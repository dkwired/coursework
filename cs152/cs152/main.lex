/* 
Name : Nicholas Glasser
SID  : 860934667
EMAIL: nglas001@ucr.edu

Name : David Klein
SID  : 860880664
EMAIL: dklei003@ucr.edu

*/
%{
	#include "y.tab.h"
	#include<string.h>
%}
DIGIT	[0-9]
IDENTIFIER [a-zA-Z]([_]*[a-zA-Z0-9]+)*
%%
"program" { return PROGRAM;} 
"beginprogram" { return BEGINPROGRAM; }
"endprogram" { return ENDPROGRAM; }
"array" { return ARRAY; }
"if" { return IF; }
"of" { return OF; }
"else" { return ELSE; }
"while" { return WHILE; }
"then" { return THEN; }
"do" { return DO; }
"read" { return READ; }
"write" { return WRITE; }
"beginloop" { return BEGINLOOP; }
"endloop" { return ENDLOOP; }
"continue" { return CONTINUE; }
"endif" { return ENDIF; }
"or" { return OR; }
"not" { return NOT; }
"true" { return TRUE; }
"false" { return FALSE; }
"and" { return AND; }
"integer" { return INT; }
{DIGIT}+ { yylval.op_val = strdup(yytext); return NUM; }
{IDENTIFIER}+ { yylval.op_val = strdup(yytext); return IDENT; }
"##".*  {}
"%"	{ yylval.op_val = yytext; return MOD;}
"+"	{ yylval.op_val = yytext; return PLUS;}
"-"	{ yylval.op_val = yytext; return MIN;}
"*"	{ yylval.op_val = yytext; return MULT;}
"/"	{ yylval.op_val = yytext; return DIV;}
"="	{ yylval.op_val = yytext; return EQUAL;}
"("	{ yylval.op_val = yytext; return LPAR;}
")"	{ yylval.op_val = yytext; return RPAR;}
";"	{ yylval.op_val = yytext; return SEMI;}
":"	{ yylval.op_val = yytext; return COLON;}
","	{ yylval.op_val = yytext; return COMMA;}
":="	{ yylval.op_val = yytext; return ASSIGN;}
"=="	{ yylval.op_val = yytext; return EQUALTO;}
"<>"	{ yylval.op_val = yytext; return NOTEQUAL;}
"<"	{ yylval.op_val = yytext; return LTHAN;}
">"	{ yylval.op_val = yytext; return GTHAN;}
"<="	{ yylval.op_val = yytext; return LETO;}
">="	{ yylval.op_val = yytext; return GETO;}
[\n]	{  }

[\t ]		{}
		
.		{
		  printf ( "Error: Unrecognized Character %s", yytext );
		}

%%

