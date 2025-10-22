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

#ifndef YY_YY_GPT_TAB_H_INCLUDED
# define YY_YY_GPT_TAB_H_INCLUDED
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
    CLASS = 258,                   /* CLASS  */
    CURLBRACKET_OPEN = 259,        /* CURLBRACKET_OPEN  */
    CURLBRACKET_CLOSE = 260,       /* CURLBRACKET_CLOSE  */
    SEMI_COLON = 261,              /* SEMI_COLON  */
    COMA = 262,                    /* COMA  */
    SQUBRACKET_OPEN = 263,         /* SQUBRACKET_OPEN  */
    SQUBRACKET_CLOSE = 264,        /* SQUBRACKET_CLOSE  */
    POINT = 265,                   /* POINT  */
    BRACKET_OPEN = 266,            /* BRACKET_OPEN  */
    BRACKET_CLOSE = 267,           /* BRACKET_CLOSE  */
    BOOLEAN = 268,                 /* BOOLEAN  */
    INT = 269,                     /* INT  */
    PUBLIC = 270,                  /* PUBLIC  */
    STATIC = 271,                  /* STATIC  */
    VOID = 272,                    /* VOID  */
    EXTENDS = 273,                 /* EXTENDS  */
    MAIN_C = 274,                  /* MAIN_C  */
    STRING_C = 275,                /* STRING_C  */
    RETURN = 276,                  /* RETURN  */
    SET = 277,                     /* SET  */
    IDENT = 278,                   /* IDENT  */
    NEW = 279,                     /* NEW  */
    THIS = 280,                    /* THIS  */
    NULL = 281,                    /* NULL  */
    TRUE = 282,                    /* TRUE  */
    FALSE = 283,                   /* FALSE  */
    NOT = 284,                     /* NOT  */
    EQUALS = 285,                  /* EQUALS  */
    OR = 286,                      /* OR  */
    AND = 287,                     /* AND  */
    DIFFERENT = 288,               /* DIFFERENT  */
    SMALLER = 289,                 /* SMALLER  */
    SMALLER_OR_EQUAL = 290,        /* SMALLER_OR_EQUAL  */
    BIGGER = 291,                  /* BIGGER  */
    BIGGER_OR_EQUAL = 292,         /* BIGGER_OR_EQUAL  */
    INSTANCE_OF = 293,             /* INSTANCE_OF  */
    PLUS = 294,                    /* PLUS  */
    MINUS = 295,                   /* MINUS  */
    TIMES = 296,                   /* TIMES  */
    DIVIDE = 297,                  /* DIVIDE  */
    REMAIN = 298,                  /* REMAIN  */
    FOR = 299,                     /* FOR  */
    IF = 300,                      /* IF  */
    ELSE = 301,                    /* ELSE  */
    INTEGER = 302,                 /* INTEGER  */
    STRING = 303,                  /* STRING  */
    EOF = 304,                     /* EOF  */
    MAIN = 305,                    /* MAIN  */
    LOWER_THAN_ELSE = 306,         /* LOWER_THAN_ELSE  */
    NEGATIVE = 307,                /* NEGATIVE  */
    CAST = 308                     /* CAST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GPT_TAB_H_INCLUDED  */
