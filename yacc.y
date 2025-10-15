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
%token PLUS MINES TIMES DIVIDE REMAIN NEGATIVE CAST
%token MAIN
%token INTEGER STRING
%token FOR IF ELSE

/* Operator precedence and associativity (optional but common) */
%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS MINES
%left TIMES DIVIDE REMAIN
%left NEGATIVE NOT CAST
%left POINT


%%
/* Grammar rules and semantic actions */

file:
    class_star class_Main EOF
    ;

class:
    CLASS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
    | CLASS IDENT EXTENDS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
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
    CLASS MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE
    ;

expr:
    INTEGER
    | STRING
    | TRUE 
    | FALSE
    | THIS
    | NULL
    | BRACKET_OPEN expr BRACKET_CLOSE
    | IDENT
    | expr POINT IDENT
    | IDENT SET expr
    | expr POINT IDENT SET expr
    | IDENT BRACKET_OPEN lexpr_opt  BRACKET_CLOSE
    | expr POINT IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    | NOT expr
    | NEGATIVE expr
    | expr binop expr
    | BRACKET_OPEN type BRACKET_CLOSE expr
    | expr INSTANCE_OF type
    ;

binop:
    EQUALS 
    | DIFFERENT 
    | SMALLER 
    | SMALLER_OR_EQUAL 
    | BIGGER 
    | BIGGER_OR_EQUAL 
    | PLUS 
    | MINES 
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
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt SEMI_COLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt SEMI_COLON

    | FOR BRACKET_OPEN SEMI_COLON SEMI_COLON BRACKET_CLOSE stmt SEMI_COLON                  
    | FOR BRACKET_OPEN SEMI_COLON SEMI_COLON stmt BRACKET_CLOSE stmt SEMI_COLON              
    | FOR BRACKET_OPEN SEMI_COLON stmt SEMI_COLON BRACKET_CLOSE stmt SEMI_COLON              
    | FOR BRACKET_OPEN SEMI_COLON stmt SEMI_COLON stmt BRACKET_CLOSE stmt SEMI_COLON        
    | FOR BRACKET_OPEN stmt SEMI_COLON SEMI_COLON BRACKET_CLOSE stmt SEMI_COLON              
    | FOR BRACKET_OPEN stmt SEMI_COLON SEMI_COLON stmt BRACKET_CLOSE stmt SEMI_COLON         
    | FOR BRACKET_OPEN stmt SEMI_COLON stmt SEMI_COLON BRACKET_CLOSE stmt SEMI_COLON        
    | FOR BRACKET_OPEN stmt SEMI_COLON stmt SEMI_COLON stmt BRACKET_CLOSE stmt SEMI_COLON    

    | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE SEMI_COLON
    | RETURN /*empty*/ SEMI_COLON
    | RETURN expr SEMI_COLON
;

params_opt:
    params
    | /* empty */
    ;

lexpr_opt:
    lexpr
    | /* empty */
    ;


class_star:
    class class_star
    | /* empty */
    ;

stmt_star:
    stmt stmt_star
    | /* empty */
    ;

decl_star:
    decl decl_star
    | /* empty */
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