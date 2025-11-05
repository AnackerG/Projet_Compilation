/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_PARSER_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENT = 258,                   /* IDENT  */
    STRING = 259,                  /* STRING  */
    INTEGER = 260,                 /* INTEGER  */
    CLASS = 261,                   /* CLASS  */
    CURLBRACKET_OPEN = 262,        /* CURLBRACKET_OPEN  */
    CURLBRACKET_CLOSE = 263,       /* CURLBRACKET_CLOSE  */
    SEMI_COLON = 264,              /* SEMI_COLON  */
    COMA = 265,                    /* COMA  */
    SQUBRACKET_OPEN = 266,         /* SQUBRACKET_OPEN  */
    SQUBRACKET_CLOSE = 267,        /* SQUBRACKET_CLOSE  */
    POINT = 268,                   /* POINT  */
    BRACKET_OPEN = 269,            /* BRACKET_OPEN  */
    BRACKET_CLOSE = 270,           /* BRACKET_CLOSE  */
    BOOLEAN = 271,                 /* BOOLEAN  */
    INT = 272,                     /* INT  */
    PUBLIC = 273,                  /* PUBLIC  */
    STATIC = 274,                  /* STATIC  */
    VOID = 275,                    /* VOID  */
    EXTENDS = 276,                 /* EXTENDS  */
    MAIN_C = 277,                  /* MAIN_C  */
    STRING_C = 278,                /* STRING_C  */
    RETURN = 279,                  /* RETURN  */
    SET = 280,                     /* SET  */
    NEW = 281,                     /* NEW  */
    THIS = 282,                    /* THIS  */
    NULL_TOKEN = 283,              /* NULL_TOKEN  */
    TRUE = 284,                    /* TRUE  */
    FALSE = 285,                   /* FALSE  */
    NOT = 286,                     /* NOT  */
    EQUALS = 287,                  /* EQUALS  */
    OR = 288,                      /* OR  */
    AND = 289,                     /* AND  */
    DIFFERENT = 290,               /* DIFFERENT  */
    SMALLER = 291,                 /* SMALLER  */
    SMALLER_OR_EQUAL = 292,        /* SMALLER_OR_EQUAL  */
    BIGGER = 293,                  /* BIGGER  */
    BIGGER_OR_EQUAL = 294,         /* BIGGER_OR_EQUAL  */
    INSTANCE_OF = 295,             /* INSTANCE_OF  */
    PLUS = 296,                    /* PLUS  */
    MINUS = 297,                   /* MINUS  */
    TIMES = 298,                   /* TIMES  */
    DIVIDE = 299,                  /* DIVIDE  */
    REMAIN = 300,                  /* REMAIN  */
    FOR = 301,                     /* FOR  */
    IF = 302,                      /* IF  */
    ELSE = 303,                    /* ELSE  */
    EOF_TOKEN = 304,               /* EOF_TOKEN  */
    MAIN = 305,                    /* MAIN  */
    LOWER_THAN_ELSE = 306,         /* LOWER_THAN_ELSE  */
    NEGATIVE = 307,                /* NEGATIVE  */
    CAST = 308                     /* CAST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser/grammar.y"

    int ival;
    char* str;

#line 122 "parser/grammar.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_GRAMMAR_TAB_H_INCLUDED  */
