digit   [0-9]
ee       [eE]
%{
int num_ints = 0;
int num_ops = 0;
int num_pars = 0;
int num_equals = 0;
%}
%%
{digit}*               {printf("%s", yytext); num_ints++;}
{digit}*"."{digit}*    {printf("%s", yytext); num_ints++;}
{digit}*ee"+"{digit}*   {printf("%s", yytext); num_ints++;}
{digit}*ee"-"{digit}*   {printf("%s", yytext); num_ints++;}
"+"|"-"|"*"|"/"         {printf ("%s", yytext ); num_ops++;}
"("|")"                 {printf ("%s", yytext ); num_pars++;}
"="                     {printf ("%s", yytext ); num_equals++;}
\n                      {;}
.                       {printf ( "Error: Unrecognized Character %s", yytext );}

%%
int main(int argc, char **argv)
{
        ++argv, --argc;
        if (argc > 0) yyin = fopen(argv[0], "r");
        else yyin = stdin;
        yylex();
        return 0;
}
