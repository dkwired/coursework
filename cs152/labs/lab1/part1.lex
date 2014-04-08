DIGIT [0-9]
ALPHABET [a-zA-Z]
%%

{DIGIT}+ {printf("%s", yytext);}
"+"|"-"|"/"|"*" {printf("%s", yytext);}
"("|")"		{printf("%s", yytext);}
{ALPHABET}+	{printf("Error: %s", yytext);}
\n		{printf("%s", yytext);}

%%

int main()
{
	yylex();
}
