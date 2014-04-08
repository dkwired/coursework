#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

int OpenListener(int port)
{
	int sd;
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		perror("can't bind port");
		abort();
	}
	if( listen(sd, 10) != 0 )
	{
		perror("Can't configure listening port");
		abort();
	}

	return sd;
}

int main(int argc, char *argv[])
{
	if ( argc != 3 )
	{
		printf("usage: %s -port <portnum>\n", argv[0]);
		exit(0);
	}

	char *portnum = argv[2];

	SSL_METHOD * method = SSLv2_server_method();	/* create new server-method instance */
	SSL_CTX * ctx = SSL_CTX_new(method);		/* create new context from method */

	int server = OpenListener(atoi(portnum));	/* create server socket */

	int actualRead, actualWritten, mdlen;
	char mdbuf[EVP_MAX_MD_SIZE];
	char buf[1024];

	while(1)
	{
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		SSL *ssl;

		int client = accept(server, (struct sockaddr*)&addr, &len);	/* accept client connection */
		printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		ssl = SSL_new(ctx);		/* get new SSL state with context */
		SSL_set_fd(ssl, client);	/* set connection socket to SSL state */

		if ( SSL_accept(ssl) == -1 )     /* do SSL-protocol accept */
			printf("Error establishing SSL-protocol accept\n");
		else
		{
			/* get public rsa key */
			char publickey[] = "rsapublickey.pem";
			BIO * publicbp = BIO_new_file(publickey, "r");
			RSA * rsa_public = PEM_read_bio_RSAPublicKey( publicbp, NULL, NULL, NULL);

			/* get private rsa key */
			char privatekey[] = "rsaprivatekey.pem";
			BIO * privatebp = BIO_new_file(privatekey, "r");
			RSA * rsa_private = PEM_read_bio_RSAPrivateKey( privatebp, NULL, NULL, NULL);

			actualRead = SSL_read(ssl, buf, sizeof(buf)); /* get request */

			/* Receive an encrypted challenge from the client and decrypt it using the RSA private key */
			actualWritten = RSA_private_decrypt( sizeof(buf), (const unsigned char *)buf, (unsigned char*)mdbuf, rsa_private, RSA_PKCS1_PADDING);
			/*  Hash the challenge using SHA1 */
			unsigned char hash[1024];
			unsigned char signedhash[1024];
			strcpy((char*)hash, (char*)mdbuf);
			SHA1(hash, sizeof(hash), signedhash);
			
			/*  Send the signed hash to the client */
			actualWritten = RSA_private_encrypt( sizeof(signedhash), (const unsigned char *)signedhash, (unsigned char*)mdbuf, rsa_private, RSA_PKCS1_PADDING);
			SSL_write(ssl, mdbuf, actualWritten);

			/*  Receive a ﬁlename request from the client */
			actualRead = SSL_read(ssl, buf, sizeof(buf));

			/* Send the (entire) requested ﬁle back to the client */
			BIO * binfile = BIO_new_file(buf, "r");
			char* buffer[1024];
			while((actualRead = BIO_read(binfile, buffer, 1024)) >= 1)
			{
				actualWritten = SSL_write(ssl, buffer, actualRead);
			}

			/* free BIOs and close the connection */
			BIO_free(publicbp);
			BIO_free(privatebp);
			BIO_free_all(binfile);
			SSL_free(ssl);	/* release SSL state */
		}		
	}

	close(server);			/* close server socket */
    	SSL_CTX_free(ctx);		/* release context */

	return 0;
}
