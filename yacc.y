%{
/* C declarations (included in the generated parser file) */
#include <stdio.h>
#include <stdlib.h>
%}

/* Bison declarations */
%token CLASS
%token CURLBRACKET_OPEN CURLBRACKET_CLOSE SEMI_COLON COMA SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT
%token PUBLIC STATIC VOID EXTENDS MAIN_C STRING_C RETURN
%token SET IDENT
%token NEW THIS
%token NULL EOF TRUE FALSE
%token NOT EQUALS OR AND DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS MINUS TIMES DIVIDE REMAIN NEGATIVE CAST
%token MAIN
%token INTEGER STRING
%token FOR IF 
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* Operator precedence and associativity (optional but common) */
%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS MINUS
%left TIMES DIVIDE REMAIN
%left NEGATIVE NOT CAST
%left POINT


%%
/* Grammar rules and semantic actions */

file:
    CLASS class_Main
    | CLASS 
    class_star class_Main EOF
    ;

class:
    IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS
    | IDENT EXTENDS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS
    ;

decl:
    type IDENT SEMI_COLON 
    | constructor
    | method
    ;

constructor:
    IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE

method:
    type IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    | VOID IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    ;

params:
    type IDENT
    | type IDENT COMA params
    ;

type: BOOLEAN
    | INT
    | IDENT
    ;

class_Main:
    MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE
    ;

expr:
    INTEGER
    | STRING
    | TRUE 
    | FALSE
    | THIS
    | NULL
    | BRACKET_OPEN expr BRACKET_CLOSE
    | IDENT expr_ident
    | expr expr_expr
    | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    | NOT expr
    | NEGATIVE expr
    | BRACKET_OPEN type BRACKET_CLOSE expr
    ;

expr_ident:
    /* empty*/
    | SET expr
    | BRACKET_OPEN lexpr_opt  BRACKET_CLOSE
    ;

expr_expr:
    POINT IDENT
    | POINT IDENT SET expr
    | POINT IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    | binop expr
    | INSTANCE_OF type
    ;

binop:
    EQUALS 
    | DIFFERENT 
    | SMALLER 
    | SMALLER_OR_EQUAL 
    | BIGGER 
    | BIGGER_OR_EQUAL 
    | PLUS 
    | MINUS 
    | TIMES 
    | DIVIDE 
    | REMAIN 
    | AND 
    | OR
    ;

lexpr:
    expr
    | expr COMA lexpr
    ;

stmt :
    /* empty */ SEMI_COLON
    | expr SEMI_COLON
    | type IDENT SEMI_COLON
    | type IDENT SET expr SEMI_COLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE %prec LOWER_THAN_ELSE stmt SEMI_COLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt SEMI_COLON       
    | FOR BRACKET_OPEN expr_opt SEMI_COLON expr_opt SEMI_COLON expr_opt BRACKET_CLOSE stmt SEMI_COLON    

    | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE SEMI_COLON
    | RETURN /*empty*/ SEMI_COLON
    | RETURN expr SEMI_COLON
;

params_opt:
    params
    | /* empty */
    ;

expr_opt:
    expr
    | /* empty */
    ;

lexpr_opt:
    lexpr
    | /* empty */
    ;


class_star:
    class_star class
  | class
  ;

stmt_star:
    stmt_star stmt
    | stmt
    ;

decl_star:
    decl_star decl
    | decl
    ;

%%
/* C helper code section */

int main(void) {
    yyparse();  /* Start the parser */
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}