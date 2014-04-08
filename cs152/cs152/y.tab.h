/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     ENDPROGRAM = 259,
     BEGINPROGRAM = 260,
     ARRAY = 261,
     IF = 262,
     OF = 263,
     INT = 264,
     THEN = 265,
     ELSE = 266,
     ENDIF = 267,
     WHILE = 268,
     DO = 269,
     READ = 270,
     ENDLOOP = 271,
     BEGINLOOP = 272,
     WRITE = 273,
     CONTINUE = 274,
     OR = 275,
     NOT = 276,
     AND = 277,
     TRUE = 278,
     FALSE = 279,
     EQUAL = 280,
     LINE = 281,
     PLUS = 282,
     MIN = 283,
     DIV = 284,
     MULT = 285,
     MOD = 286,
     LPAR = 287,
     RPAR = 288,
     SEMI = 289,
     COLON = 290,
     COMMA = 291,
     LETO = 292,
     GETO = 293,
     LTHAN = 294,
     GTHAN = 295,
     NOTEQUAL = 296,
     EQUALTO = 297,
     ASSIGN = 298,
     NUM = 299,
     IDENT = 300
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define ENDPROGRAM 259
#define BEGINPROGRAM 260
#define ARRAY 261
#define IF 262
#define OF 263
#define INT 264
#define THEN 265
#define ELSE 266
#define ENDIF 267
#define WHILE 268
#define DO 269
#define READ 270
#define ENDLOOP 271
#define BEGINLOOP 272
#define WRITE 273
#define CONTINUE 274
#define OR 275
#define NOT 276
#define AND 277
#define TRUE 278
#define FALSE 279
#define EQUAL 280
#define LINE 281
#define PLUS 282
#define MIN 283
#define DIV 284
#define MULT 285
#define MOD 286
#define LPAR 287
#define RPAR 288
#define SEMI 289
#define COLON 290
#define COMMA 291
#define LETO 292
#define GETO 293
#define LTHAN 294
#define GTHAN 295
#define NOTEQUAL 296
#define EQUALTO 297
#define ASSIGN 298
#define NUM 299
#define IDENT 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "mini_l.y"
{
	int val;
	char * op_val; 
}
/* Line 1529 of yacc.c.  */
#line 144 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

