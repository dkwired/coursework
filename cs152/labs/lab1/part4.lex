%{
int integers = 0;
int operators = 0;
int parentheses = 0;
int equalsigns = 0;
%}
DIGIT [0-9]
ALPHABET [a-zA-Z]
%%
{DIGIT}+ 		{integers++;}
{DIGIT}+"."{DIGIT}+ 	{integers++;}
{DIGIT}+"e"|"E"{DIGIT}+"+" {integers++;}
{DIGIT}+"e"|"E"{DIGIT}+"-" {integers++;}
"+"|"-"|"/"|"*" 	{operators++;}
"("|")"			{parentheses++;}
"="			{equalsigns++;}
\n			{
				printf("Number of integers: %d", integers);
				printf("Number of operators: %d", operators);
				printf("Number of parentheses: %d", parentheses);
				printf("Number of equalsigns: %d", equalsigns);
				integers = operators = parentheses = equalsigns = 0;
				cout << endl;
			}
.			{printf("Error: %s", yytext);}
%%
int main(int argc, char **argv)
{
	++argv, --argc; /* skip over program name */
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;

	yylex();
}
