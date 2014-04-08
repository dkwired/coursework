#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

int OpenConnection(const char *serveraddress, int port)
{   
	int sd;
	struct hostent *host;
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = *(long*)(host->h_addr);
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		close(sd);
		printf("Error establishing connection with host");
		exit(0);
	}
	return sd;
}

int main(int argc, char *argv[])
{
	SSL_CTX *ctx;
	SSL_METHOD *method;

	int server;
	SSL *ssl;
	char buf[1024];
	int bytes;
	char *serveraddress, *portnum, *filename;
	
	if ( argc != 6 )
	{
		printf("usage: %s -server <serveraddress> -port <portnum> filename\n", argv[0]);
		exit(0);
	}

	serveraddress = argv[2];
	portnum = argv[4];
	filename = argv[5];

	method = SSLv2_client_method();
	ctx = SSL_CTX_new(method);

	server = OpenConnection(serveraddress, atoi(portnum));
	ssl = SSL_new(ctx);      /* create new SSL connection state */
	SSL_set_fd(ssl, server);    /* attach the socket descriptor */

	if ( SSL_connect(ssl) == -1 )   /* perform the connection */
		ERR_print_errors_fp(stderr);
	else
	{
		int randnum = 5555;
		char *msg = (char*)randnum;

		//printf("Connected with %s encryption\n", SSL_get_cipher(ssl));

		char publickey[] = "/server/rsapublickey.pem";
		BIO * bp = BIO_new_file(publickey, "r");
		RSA * rsa_public = PEM_read_bio_RSAPublicKey( bp, NULL, NULL, NULL);

		int actualRead, actualWritten;
		char mdbuf[EVP_MAX_MD_SIZE];
		int mdlen = sizeof(msg);

		/* encrypt & send message */
		actualWritten = RSA_public_encrypt( mdlen, (const unsigned char *)msg, (unsigned char*)mdbuf, rsa_public, RSA_PKCS1_PADDING);
		SSL_write(ssl, mdbuf, actualWritten);

		/*  Hash the challenge using SHA1 */
		unsigned char hash[1024];
		unsigned char signedhash[1024];
		strcpy((char*)hash, (char*)mdbuf);
		SHA1(hash, sizeof(hash), signedhash);

		/* get reply & decrypt */
		bytes = SSL_read(ssl, buf, sizeof(buf));
		buf[bytes] = 0;
		printf("Received: \"%s\"\n", buf);
		actualRead = RSA_public_decrypt( mdlen, (const unsigned char *)buf, (unsigned char*)mdbuf, rsa_public, RSA_PKCS1_PADDING);
		printf("Decrypted: \"%s\"\n", mdbuf);

		/* Compare the generated and recovered hashes above, to verify that the server received and decrypted the challenge properly */
		string string1 = string((char*)signedhash);
		string string2 = string(mdbuf);

		if( string1 == string2 )
		{
			/* Send the server a ﬁlename (ﬁle request) */
			actualWritten = SSL_write(ssl, filename, strlen(filename));

			/* Receive and display the contents of the ﬁle requested */
			while((actualRead = SSL_read(ssl, buf, sizeof(buf))) >= 1)
			{
				printf("%s", buf);
			}
		}
		else printf("Messages do no match!");

		SSL_free(ssl);        /* release connection state */
		BIO_free(bp);
	}
	close(server);         /* close socket */
	SSL_CTX_free(ctx);        /* release context */
	return 0; 
}
