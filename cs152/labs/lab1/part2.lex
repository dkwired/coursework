DIGIT [0-9]
ALPHABET [a-zA-Z]
%%

{DIGIT}+ {printf("%s", yytext);}
"+"|"-"|"/"|"*" {printf("%s", yytext);}
"("|")"		{printf("%s", yytext);}
{ALPHABET}+	{printf("Error: %s", yytext); exit(1);}
\n		{printf("%s", yytext);}

%%

int main(int argc, char **argv)
{
	++argv, --argc;	/* skip over program name */
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;
	yylex();
}
