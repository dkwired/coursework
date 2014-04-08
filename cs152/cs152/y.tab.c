/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 12 "mini_l.y"
 
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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "mini_l.y"
{
	int val;
	char * op_val; 
}
/* Line 193 of yacc.c.  */
#line 220 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 233 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNRULES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    15,    16,    21,    22,
      23,    28,    29,    35,    36,    38,    39,    40,    46,    47,
      48,    49,    50,    51,    61,    62,    63,    68,    70,    72,
      74,    76,    78,    80,    82,    83,    88,    89,    90,    99,
     100,   101,   105,   106,   107,   115,   116,   117,   118,   119,
     130,   131,   135,   136,   140,   141,   143,   144,   149,   152,
     155,   156,   157,   162,   163,   164,   169,   174,   177,   180,
     181,   187,   188,   190,   192,   194,   196,   198,   200,   202,
     205,   206,   210,   215,   218,   219,   223,   227,   231,   234,
     237,   242,   243,   245,   247,   248
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    -1,    -1,    -1,     3,    48,    45,    49,
      34,    50,    51,     4,    -1,    -1,    53,     5,    52,    65,
      -1,    -1,    -1,    55,    34,    54,    53,    -1,    -1,    57,
      35,    56,    60,     9,    -1,    -1,    45,    -1,    -1,    -1,
      45,    58,    36,    59,    57,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    61,    32,    62,    44,    63,    33,    64,     8,
      -1,    -1,    -1,    67,    34,    66,    65,    -1,    68,    -1,
      70,    -1,    75,    -1,    78,    -1,    83,    -1,    85,    -1,
      19,    -1,    -1,   105,    43,    69,    99,    -1,    -1,    -1,
       7,    71,    89,    10,    72,    65,    73,    12,    -1,    -1,
      -1,    11,    74,    65,    -1,    -1,    -1,    13,    76,    89,
      17,    77,    65,    16,    -1,    -1,    -1,    -1,    -1,    14,
      79,    17,    80,    65,    16,    81,    13,    82,    89,    -1,
      -1,    15,    84,    87,    -1,    -1,    18,    86,    87,    -1,
      -1,   105,    -1,    -1,   105,    36,    88,    87,    -1,    90,
      91,    -1,    95,    93,    -1,    -1,    -1,    20,    92,    90,
      91,    -1,    -1,    -1,    22,    94,    95,    93,    -1,    97,
      99,    98,    99,    -1,    97,    23,    -1,    97,    24,    -1,
      -1,    97,    32,    96,    89,    33,    -1,    -1,    21,    -1,
      42,    -1,    39,    -1,    40,    -1,    41,    -1,    37,    -1,
      38,    -1,   101,   100,    -1,    -1,    27,   101,   100,    -1,
      28,   101,   100,   100,    -1,   103,   102,    -1,    -1,    30,
     103,   102,    -1,    29,   103,   102,    -1,    31,   103,   102,
      -1,   104,   105,    -1,   104,    44,    -1,   104,    32,    99,
      33,    -1,    -1,    28,    -1,    45,    -1,    -1,    45,    32,
     106,    99,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   107,   110,   105,   116,   115,   120,   122,
     121,   127,   126,   131,   132,   133,   134,   133,   137,   138,
     139,   140,   141,   138,   144,   146,   145,   150,   151,   152,
     153,   154,   155,   156,   160,   159,   164,   166,   164,   171,
     172,   172,   176,   178,   176,   183,   184,   186,   187,   183,
     191,   191,   195,   195,   198,   199,   201,   200,   205,   209,
     212,   213,   213,   217,   218,   218,   223,   226,   227,   228,
     228,   232,   233,   236,   237,   238,   239,   240,   241,   244,
     247,   248,   256,   267,   272,   273,   281,   289,   298,   300,
     301,   305,   306,   310,   314,   313
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ENDPROGRAM", "BEGINPROGRAM",
  "ARRAY", "IF", "OF", "INT", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "READ", "ENDLOOP", "BEGINLOOP", "WRITE", "CONTINUE", "OR", "NOT", "AND",
  "TRUE", "FALSE", "EQUAL", "LINE", "PLUS", "MIN", "DIV", "MULT", "MOD",
  "LPAR", "RPAR", "SEMI", "COLON", "COMMA", "LETO", "GETO", "LTHAN",
  "GTHAN", "NOTEQUAL", "EQUALTO", "ASSIGN", "NUM", "IDENT", "$accept",
  "program", "@1", "@2", "@3", "block", "@4", "decl_block", "@5",
  "declaration", "@6", "ident_block", "@7", "@8", "array_block", "@9",
  "@10", "@11", "@12", "stmt_block", "@13", "statement", "stmt_var", "@14",
  "stmt_if", "@15", "@16", "stmt_else", "@17", "stmt_while", "@18", "@19",
  "stmt_do", "@20", "@21", "@22", "@23", "stmt_read", "@24", "stmt_write",
  "@25", "var_block", "@26", "bool_exp", "relation_and_expression",
  "relation_and_expression_block", "@27", "relation_expression_block",
  "@28", "relation_expression", "@29", "not_rule", "compare", "expression",
  "multi_exp_block", "multi_exp", "term_block", "term", "min_rule", "var",
  "@30", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    48,    49,    50,    47,    52,    51,    53,    54,
      53,    56,    55,    57,    57,    58,    59,    57,    60,    61,
      62,    63,    64,    60,    65,    66,    65,    67,    67,    67,
      67,    67,    67,    67,    69,    68,    71,    72,    70,    73,
      74,    73,    76,    77,    75,    79,    80,    81,    82,    78,
      84,    83,    86,    85,    87,    87,    88,    87,    89,    90,
      91,    92,    91,    93,    94,    93,    95,    95,    95,    96,
      95,    97,    97,    98,    98,    98,    98,    98,    98,    99,
     100,   100,   100,   101,   102,   102,   102,   102,   103,   103,
     103,   104,   104,   105,   106,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     4,     0,     0,
       4,     0,     5,     0,     1,     0,     0,     5,     0,     0,
       0,     0,     0,     9,     0,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     0,     8,     0,
       0,     3,     0,     0,     7,     0,     0,     0,     0,    10,
       0,     3,     0,     3,     0,     1,     0,     4,     2,     2,
       0,     0,     4,     0,     0,     4,     4,     2,     2,     0,
       5,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     3,     4,     2,     0,     3,     3,     3,     2,     2,
       4,     0,     1,     1,     0,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     0,     1,     3,     0,     4,     8,    14,
       0,     0,     0,     0,     0,     5,     6,     9,    11,    16,
      24,     8,    18,    13,    36,    42,    45,    50,    52,    33,
      93,     7,     0,    27,    28,    29,    30,    31,    32,     0,
      10,    19,     0,    17,    71,    71,     0,    54,    54,    94,
      25,    34,     0,    12,    72,     0,    60,    63,    91,     0,
      46,    51,    55,    53,    91,    24,    91,    20,    37,    61,
      58,    64,    59,    67,    68,    92,    69,     0,    80,    84,
       0,    43,    24,    56,     0,    26,    35,     0,    24,    71,
      71,    71,    77,    78,    74,    75,    76,    73,    91,    91,
      91,    79,    91,    91,    91,    83,    91,    89,    88,    24,
       0,    54,    95,    21,    39,    60,    63,     0,    66,    80,
      80,    84,    84,    84,     0,     0,    47,    57,     0,    40,
       0,    62,    65,    70,    81,    80,    86,    85,    87,    90,
      44,     0,    22,    24,    38,    82,    48,     0,    41,    71,
      23,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,    10,    20,    11,    21,    12,
      22,    13,    14,    23,    42,    52,    87,   128,   147,    31,
      65,    32,    33,    66,    34,    44,    88,   130,   143,    35,
      45,   109,    36,    46,    82,   141,   149,    37,    47,    38,
      48,    61,   111,    55,    56,    70,    89,    72,    90,    57,
      91,    58,    98,    77,   101,    78,   105,    79,    80,    39,
      64
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int8 yypact[] =
{
       5,  -109,     6,   -35,  -109,  -109,   -21,  -109,   -26,   -19,
      11,    18,     4,    27,    15,  -109,  -109,  -109,  -109,  -109,
       7,   -26,    34,    19,  -109,  -109,  -109,  -109,  -109,  -109,
      31,  -109,    32,  -109,  -109,  -109,  -109,  -109,  -109,    25,
    -109,  -109,    60,  -109,    49,    49,    54,    28,    28,  -109,
    -109,  -109,    40,  -109,  -109,    64,    55,    56,     9,    59,
    -109,  -109,    41,  -109,    52,     7,    52,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,    16,     3,    13,
     -16,  -109,     7,  -109,    48,  -109,  -109,    38,     7,    49,
      49,    49,  -109,  -109,  -109,  -109,  -109,  -109,    52,    52,
      52,  -109,    52,    52,    52,  -109,    52,  -109,  -109,     7,
      67,    28,  -109,  -109,    73,    55,    56,    53,  -109,     3,
       3,    13,    13,    13,    57,    69,  -109,  -109,    58,  -109,
      75,  -109,  -109,  -109,  -109,     3,  -109,  -109,  -109,  -109,
    -109,    76,  -109,     7,  -109,  -109,  -109,    80,  -109,    49,
    -109,  -109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -109,  -109,  -109,  -109,  -109,  -109,  -109,    71,  -109,  -109,
    -109,    70,  -109,  -109,  -109,  -109,  -109,  -109,  -109,   -64,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,   -46,  -109,   -45,     8,   -20,  -109,   -22,  -109,    10,
    -109,  -109,  -109,   -59,  -108,   -65,   -73,   -43,  -109,   -44,
    -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int16 yytable[] =
{
      59,    85,    63,    62,    62,    84,     4,    86,     1,   -13,
       5,   134,   135,     7,    24,    15,   106,   -15,   110,     9,
      25,    26,    27,    16,   114,    28,    29,   145,   107,    30,
      99,   100,    73,    74,   119,   120,   108,    75,    17,   118,
      41,    76,   102,   103,   104,   125,   117,   124,   136,   137,
     138,    19,    30,    92,    93,    94,    95,    96,    97,   121,
     122,   123,    18,    49,     9,   127,    50,    62,    51,    53,
      54,    60,    67,    30,    68,    69,    81,    83,    71,   148,
      75,   112,   113,   126,   129,   140,   133,   144,   150,   146,
     139,   142,    40,    43,   132,   131,     0,   115,     0,     0,
     116,     0,     0,     0,   151
};

static const yytype_int16 yycheck[] =
{
      45,    65,    48,    47,    48,    64,     0,    66,     3,    35,
      45,   119,   120,    34,     7,     4,    32,    36,    82,    45,
      13,    14,    15,     5,    88,    18,    19,   135,    44,    45,
      27,    28,    23,    24,    99,   100,    80,    28,    34,    98,
       6,    32,    29,    30,    31,   109,    91,   106,   121,   122,
     123,    36,    45,    37,    38,    39,    40,    41,    42,   102,
     103,   104,    35,    32,    45,   111,    34,   111,    43,     9,
      21,    17,    32,    45,    10,    20,    17,    36,    22,   143,
      28,    33,    44,    16,    11,    16,    33,    12,     8,    13,
      33,    33,    21,    23,   116,   115,    -1,    89,    -1,    -1,
      90,    -1,    -1,    -1,   149
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    47,    48,     0,    45,    49,    34,    50,    45,
      51,    53,    55,    57,    58,     4,     5,    34,    35,    36,
      52,    54,    56,    59,     7,    13,    14,    15,    18,    19,
      45,    65,    67,    68,    70,    75,    78,    83,    85,   105,
      53,     6,    60,    57,    71,    76,    79,    84,    86,    32,
      34,    43,    61,     9,    21,    89,    90,    95,    97,    89,
      17,    87,   105,    87,   106,    66,    69,    32,    10,    20,
      91,    22,    93,    23,    24,    28,    32,    99,   101,   103,
     104,    17,    80,    36,    99,    65,    99,    62,    72,    92,
      94,    96,    37,    38,    39,    40,    41,    42,    98,    27,
      28,   100,    29,    30,    31,   102,    32,    44,   105,    77,
      65,    88,    33,    44,    65,    90,    95,    89,    99,   101,
     101,   103,   103,   103,    99,    65,    16,    87,    63,    11,
      73,    91,    93,    33,   100,   100,   102,   102,   102,    33,
      16,    81,    33,    74,    12,   100,    13,    64,    65,    82,
       8,    89
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 105 "mini_l.y"
    { init();
		printf("program -> PROGRAM\n");;}
    break;

  case 3:
#line 107 "mini_l.y"
    { /*name file here */  
	       printf("ident -> IDENT (%s", (yyvsp[(3) - (3)].op_val));
	       printf(")\n");;}
    break;

  case 4:
#line 110 "mini_l.y"
    {printf("semicolon -> SEMICOLON\n");;}
    break;

  case 5:
#line 112 "mini_l.y"
    {printf("endprogram -> ENDPROGRAM\n");;}
    break;

  case 6:
#line 116 "mini_l.y"
    {  add_statement( "Start: " ); 
			printf("beginprogram -> BEGINPROGRAM\n");;}
    break;

  case 9:
#line 122 "mini_l.y"
    {printf("semicolon -> SEMICOLON\n");;}
    break;

  case 11:
#line 127 "mini_l.y"
    {printf("colon -> COLON\n");;}
    break;

  case 12:
#line 129 "mini_l.y"
    {printf("integer -> INTEGER\n");;}
    break;

  case 14:
#line 132 "mini_l.y"
    { printf("ident -> IDENT\n");;}
    break;

  case 15:
#line 133 "mini_l.y"
    { printf("ident -> IDENT\n");;}
    break;

  case 16:
#line 134 "mini_l.y"
    {printf("comma -> COMMA\n");;}
    break;

  case 19:
#line 138 "mini_l.y"
    {printf("array -> ARRAY\n");;}
    break;

  case 20:
#line 139 "mini_l.y"
    {printf("l_paren -> _array_L_PAREN\n");;}
    break;

  case 21:
#line 140 "mini_l.y"
    { printf("num -> NUM\n %s", (yyvsp[(5) - (5)].op_val)) ;}
    break;

  case 22:
#line 141 "mini_l.y"
    {printf("r_paren -> R_PAREN\n");;}
    break;

  case 23:
#line 142 "mini_l.y"
    { printf("of -> OF\n");;}
    break;

  case 25:
#line 146 "mini_l.y"
    {printf("semicolon -> SEMICOLON\n");;}
    break;

  case 33:
#line 156 "mini_l.y"
    {printf("continue -> CONTINUE\n");;}
    break;

  case 34:
#line 160 "mini_l.y"
    {printf("assign -> ASSIGN\n");;}
    break;

  case 36:
#line 164 "mini_l.y"
    {printf("if -> IF\n");;}
    break;

  case 37:
#line 166 "mini_l.y"
    {printf("then -> THEN\n");;}
    break;

  case 38:
#line 169 "mini_l.y"
    {printf("endif -> ENDIF\n");;}
    break;

  case 40:
#line 172 "mini_l.y"
    {printf("else -> ELSE\n");;}
    break;

  case 42:
#line 176 "mini_l.y"
    {printf("while -> WHILE\n");;}
    break;

  case 43:
#line 178 "mini_l.y"
    {printf("beginloop -> BEGINLOOP\n");;}
    break;

  case 44:
#line 180 "mini_l.y"
    {printf("endloop -> ENDLOOP\n");;}
    break;

  case 45:
#line 183 "mini_l.y"
    {printf("do -> DO\n");;}
    break;

  case 46:
#line 184 "mini_l.y"
    {printf("beginloop -> BEGINLOOP\n");;}
    break;

  case 47:
#line 186 "mini_l.y"
    {printf("endloop -> ENDLOOP\n");;}
    break;

  case 48:
#line 187 "mini_l.y"
    {printf("while -> WHILE\n");;}
    break;

  case 50:
#line 191 "mini_l.y"
    {printf("read -> READ\n"); rd_write=".<";;}
    break;

  case 52:
#line 195 "mini_l.y"
    {printf("write -> write\n"); rd_write=".>";;}
    break;

  case 56:
#line 201 "mini_l.y"
    {printf("comma -> COMMA\n");;}
    break;

  case 61:
#line 213 "mini_l.y"
    {printf("or -> OR\n");;}
    break;

  case 64:
#line 218 "mini_l.y"
    {printf("and -> AND\n");;}
    break;

  case 67:
#line 226 "mini_l.y"
    {printf("true -> TRUE\n");;}
    break;

  case 68:
#line 227 "mini_l.y"
    {printf("false -> FALSE\n");;}
    break;

  case 69:
#line 228 "mini_l.y"
    {printf("l_paren -> rel_L_PAREN\n");;}
    break;

  case 70:
#line 230 "mini_l.y"
    {printf("r_paren -> R_PAREN\n");;}
    break;

  case 72:
#line 233 "mini_l.y"
    {printf("not -> NOT\n");;}
    break;

  case 73:
#line 236 "mini_l.y"
    {printf("comp -> EQ\n");;}
    break;

  case 74:
#line 237 "mini_l.y"
    {printf("comp -> LT\n");;}
    break;

  case 75:
#line 238 "mini_l.y"
    {printf("comp -> GT\n");;}
    break;

  case 76:
#line 239 "mini_l.y"
    {printf("comp -> NOTEQ\n");;}
    break;

  case 77:
#line 240 "mini_l.y"
    {printf("comp -> LTE\n");;}
    break;

  case 78:
#line 241 "mini_l.y"
    {printf("comp -> GTE\n");;}
    break;

  case 81:
#line 250 "mini_l.y"
    { sprintf(buff, "+ t%d, multi_exp, %s", tmp_cnt, (yyvsp[(3) - (3)].op_val));
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			(yyval.op_val) = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; ;}
    break;

  case 82:
#line 259 "mini_l.y"
    { sprintf(buff, "- t%d, multi_exp, %s", tmp_cnt, (yyvsp[(3) - (4)].op_val));
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			(yyval.op_val) = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; ;}
    break;

  case 83:
#line 268 "mini_l.y"
    { sprintf(buff, "= term %s", (yyvsp[(2) - (2)].op_val));
		add_statement(strdup(buff));
		(yyval.op_val) = strdup(buff); ;}
    break;

  case 85:
#line 275 "mini_l.y"
    { sprintf(buff, "* t%d, termblock, %s", tmp_cnt, (yyvsp[(3) - (3)].op_val));
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			(yyval.op_val) = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; ;}
    break;

  case 86:
#line 283 "mini_l.y"
    { sprintf(buff, "/ t%d, termblock, %s", tmp_cnt, (yyvsp[(3) - (3)].op_val));
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			(yyval.op_val) = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; ;}
    break;

  case 87:
#line 291 "mini_l.y"
    { sprintf(buff, "% t%d, termblock, %s", tmp_cnt, (yyvsp[(3) - (3)].op_val));
			add_statement(strdup(buff));
			sprintf(buff, "t%d", tmp_cnt);
			(yyval.op_val) = strdup(buff);
			add_temp(strdup(buff));
			tmp_cnt++; ;}
    break;

  case 88:
#line 298 "mini_l.y"
    { sprintf(buff, "%s %s", (yyvsp[(1) - (2)].op_val), (yyvsp[(2) - (2)].op_val));
			add_statement(strdup(buff)); ;}
    break;

  case 92:
#line 306 "mini_l.y"
    { (yyval.op_val) = strdup((yyvsp[(1) - (1)].op_val)); ;}
    break;

  case 93:
#line 310 "mini_l.y"
    { sprintf(buff, "_%s", (yyvsp[(1) - (1)].op_val));
		(yyval.op_val) = strdup(buff);
		add_var(strdup(buff));;}
    break;

  case 94:
#line 314 "mini_l.y"
    {printf("l_paren -> var_L_PAREN\n");;}
    break;

  case 95:
#line 316 "mini_l.y"
    { sprintf(buff, "=[] t%d, %s, expr", tmp_cnt, (yyvsp[(1) - (5)].op_val));
		add_statement(strdup(buff));
		sprintf(buff, "t%d", tmp_cnt);
		(yyval.op_val) = strdup(buff);
		add_temp(strdup(buff));
		tmp_cnt++; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1897 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 323 "mini_l.y"

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

