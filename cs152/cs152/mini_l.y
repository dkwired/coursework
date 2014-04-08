/* 
Name : Nicholas Glasser
SID  : 860934667
EMAIL: nglas001@ucr.edu

Name : David Klein
SID  : 860880664
EMAIL: dklei003@ucr.edu

*/

%{ 
	#include <stdio.h>
	#include <iostream>
	#include <vector>
	#include <string>

	using namespace std; 

	void yyerror(char * ); 
	extern FILE * yyin;
	int yylex();

	vector<char*> vars;
	vector<char*> temps;
	vector<char*> stmts;
	char * buff;
	char * rd_write;
	char * min_sign;
	int tmp_cnt;

	void init();
	void print_temps();
	void print_statements();
	void print_vars();
	void add_statement(char*);
	void add_temp(char*);
	void add_var(char*);
%}
%union 
{
	int val;
	char * op_val; 
}

%token PROGRAM
%token ENDPROGRAM
%token BEGINPROGRAM
%token ARRAY
%token IF
%token OF
%token INT
%token THEN
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token READ
%token ENDLOOP
%token BEGINLOOP
%token WRITE
%token CONTINUE
%token OR
%token NOT
%token AND
%token TRUE
%token FALSE

%right EQUAL

%left LINE
%left PLUS
%left <op_val> MIN
%left DIV
%left MULT
%left MOD
%left LPAR
%left RPAR
%left SEMI
%left COLON
%left COMMA
%left LETO
%left GETO
%left LTHAN
%left GTHAN
%left NOTEQUAL
%left EQUALTO
%left ASSIGN

%token <op_val> NUM
%token <op_val> IDENT

%type <op_val> var
%type <op_val> expression
%type <op_val> multi_exp_block
%type <op_val> multi_exp
%type <op_val> min_rule
%type <op_val> term
%type <op_val> term_block

%start program
%%

program:
	PROGRAM { init();
		printf("program -> PROGRAM\n");} 
        IDENT { /*name file here */  
	       printf("ident -> IDENT (%s", $3);
	       printf(")\n");}
	SEMI  {printf("semicolon -> SEMICOLON\n");}
        block
	ENDPROGRAM {printf("endprogram -> ENDPROGRAM\n");}

block:
	decl_block
	BEGINPROGRAM {  add_statement( "Start: " ); 
			printf("beginprogram -> BEGINPROGRAM\n");}
	stmt_block

decl_block: /*empty */
      |	declaration 
	SEMI  {printf("semicolon -> SEMICOLON\n");}
	decl_block

declaration:
	ident_block
	COLON {printf("colon -> COLON\n");}
	array_block
	INT {printf("integer -> INTEGER\n");}

ident_block: /* empty */
      |	IDENT { printf("ident -> IDENT\n");}
      |	IDENT { printf("ident -> IDENT\n");}
	COMMA {printf("comma -> COMMA\n");}
	ident_block

array_block:
      |	ARRAY {printf("array -> ARRAY\n");}
	LPAR {printf("l_paren -> _array_L_PAREN\n");}
	NUM { printf("num -> NUM\n %s", $5) }
	RPAR {printf("r_paren -> R_PAREN\n");}
	OF { printf("of -> OF\n");}

stmt_block: /* empty */
      |	statement
	SEMI  {printf("semicolon -> SEMICOLON\n");}
	stmt_block

statement:
        stmt_var
      | stmt_if
      | stmt_while
      | stmt_do
      | stmt_read
      | stmt_write
      | CONTINUE  {printf("continue -> CONTINUE\n");}

stmt_var:
	var
	ASSIGN {printf("assign -> ASSIGN\n");}
	expression

stmt_if:
    	IF {printf("if -> IF\n");}
	bool_exp
	THEN {printf("then -> THEN\n");}
	stmt_block
	stmt_else
	ENDIF {printf("endif -> ENDIF\n");}

stmt_else: /* empty */
      |	ELSE {printf("else -> ELSE\n");}
	stmt_block

stmt_while:
	WHILE {printf("while -> WHILE\n");}
	bool_exp
	BEGINLOOP {printf("beginloop -> BEGINLOOP\n");}
	stmt_block
	ENDLOOP {printf("endloop -> ENDLOOP\n");}

stmt_do:
	DO {printf("do -> DO\n");}
	BEGINLOOP {printf("beginloop -> BEGINLOOP\n");}
	stmt_block
	ENDLOOP {printf("endloop -> ENDLOOP\n");}
	WHILE {printf("while -> WHILE\n");}
	bool_exp

stmt_read:
	READ {printf("read -> READ\n"); rd_write=".<";}
	var_block

stmt_write:
	WRITE {printf("write -> write\n"); rd_write=".>";}
	var_block

var_block: /* empty */
      | var
      |	var
	COMMA {printf("comma -> COMMA\n");}
	var_block

bool_exp:
	relation_and_expression
	relation_and_expression_block

relation_and_expression:
	relation_expression
	relation_expression_block
	
relation_and_expression_block: /* empty */
      |	OR {printf("or -> OR\n");}
	relation_and_expression
	relation_and_expression_block

relation_expression_block: /* empty */
      |	AND {printf("and -> AND\n");}
	relation_expression
	relation_expression_block

relation_expression:
      	not_rule expression
        compare
        expression
      | not_rule TRUE {printf("true -> TRUE\n");}
      | not_rule FALSE {printf("false -> FALSE\n");}
      | not_rule LPAR {printf("l_paren -> rel_L_PAREN\n");}
        bool_exp
	RPAR {printf("r_paren -> R_PAREN\n");}

not_rule: /* empty */
      |	NOT {printf("not -> NOT\n");}

compare:
	EQUALTO {printf("comp -> EQ\n");}
      | LTHAN {printf("comp -> LT\n");}
      | GTHAN {printf("comp -> GT\n");}
      | NOTEQUAL {printf("comp -> NOTEQ\n");}
      | LETO {printf("comp -> LTE\n");} 
      | GETO {printf("comp -> GTE\n");} 

expression:
	multi_exp
	multi_exp_block

multi_exp_block: /* empty */
      | PLUS 
	multi_exp
	multi_exp_block { sprintf(buff, "+ t%d, multi_exp, %s", tmp_cnt, $3);
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			$$ = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; }
      | MIN
	multi_exp
	multi_exp_block
	multi_exp_block { sprintf(buff, "- t%d, multi_exp, %s", tmp_cnt, $3);
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			$$ = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; }

multi_exp:
	term
	term_block { sprintf(buff, "= term %s", $2);
		add_statement(strdup(buff));
		$$ = strdup(buff); }

term_block: /* empty */
      | MULT
	term
	term_block { sprintf(buff, "* t%d, termblock, %s", tmp_cnt, $3);
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			$$ = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; }
      | DIV
	term
	term_block { sprintf(buff, "/ t%d, termblock, %s", tmp_cnt, $3);
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			$$ = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; }
      | MOD
	term
	term_block { sprintf(buff, "% t%d, termblock, %s", tmp_cnt, $3);
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			$$ = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; }

term: min_rule var { sprintf(buff, "%s %s", $1, $2);
			add_statement(strdup(buff)); }
      | min_rule NUM
      |	min_rule LPAR
        expression
	RPAR

min_rule: /* empty */
      |	MIN { $$ = strdup($1); }

      
var:
	IDENT { sprintf(buff, "_%s", $1);
		$$ = strdup(buff);
		add_var(strdup(buff));}
      |	IDENT 
	LPAR {printf("l_paren -> var_L_PAREN\n");}
        expression
	RPAR { sprintf(buff, "=[] t%d, %s, expr", tmp_cnt, $1);
		add_statement(strdup(buff));
		sprintf(buff, "t%d", tmp_cnt);
		$$ = strdup(buff);
		add_temp(strdup(buff));
		tmp_cnt++; }

%%
int main(int argc, char **argv)
{
	++argv, --argc;
        if (argc > 0) yyin = fopen(argv[0], "r");
        else yyin = stdin;
	yyparse();
	print_vars();
	print_temps();
	print_statements();
	return 0;
}

void init()	// initialize variables
{
	rd_write = (char*)malloc(sizeof(256));
	min_sign = (char*)malloc(sizeof(256));
	buff = (char*)malloc(sizeof(256));
	tmp_cnt = 0;
}

void add_var( char * s )
{
	vars.push_back(s);
}

void add_statement( char * s )
{
	stmts.push_back(s);
}

void add_temp( char * s )
{
	temps.push_back(s);
}

void print_temps()
{
	for( unsigned i = 0; i < temps.size(); i++ )
	{
		printf("%s\n", temps.at(i));
	}
}
void print_statements()
{
	for( unsigned i = 0; i < stmts.size(); i++ )
	{
		printf("%s\n", stmts.at(i));
	}
}
void print_vars()
{
	for( unsigned i = 0; i < vars.size(); i++ )
	{
		printf("%s\n", vars.at(i));
	}
}
/* TODO

add statement for bool

sprintf( buff, formated string, parameters ($2, $3))
add_statement(strdup(buff))


$$ = $1

*/
void yyerror(char* errstr) {
	printf("Error: %s\n", errstr);
}
