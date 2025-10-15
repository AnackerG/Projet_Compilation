%{
/* C declarations (included in the generated parser file) */
#include <stdio.h>
#include <stdlib.h>
%}

/* Bison declarations */
%token CLASS
%token CURLBRACKET_OPEN CURLBRACKET_CLOSE SEMI_COLON COMA SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT
%token PUBLIC STATIC VOID EXTENDS MAIN_C STRING_C
%token SET
%token NEW THIS
%token NULL EOF TRUE FALSE
%token NOT EQUALS OR AND DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS MINES MULTIPLY DIVISION REMAIN NEGATIVE CAST
%token MAIN
%token INTEGER STRING

/* Operator precedence and associativity (optional but common) */
%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS MINES
%left MULTIPLY DIVISION REMAIN
%left NEGATIVE NOT CAST
%left POINT


%%
/* Grammar rules and semantic actions */

expr:
      expr PLUS expr    { printf("Add\n"); }
    | expr MINUS expr   { printf("Subtract\n"); }
    | expr TIMES expr   { printf("Multiply\n"); }
    | expr DIVIDE expr  { printf("Divide\n"); }
    | LPAREN expr RPAREN { printf("Parenthesized\n"); }
    | NUMBER            { printf("Number\n"); }
    ;

file:
    class_star class_Main EOF
    ;

class:
    CLASS ident CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
    | CLASS ident EXTENDS ident CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
    ;

decl:
    type ident SEMI_COLON 
    | constructor
    | method
    ;

constructor:
    ident BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE

method:
    type ident BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    | VOID ident BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    ;

params:
    type ident
    | type ident COMA params
    ;

type: BOOLEAN
    | INT
    | ident
    ;

class_Main:
    CLASS MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C ident SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE
    ;

expr:
    INTEGER
    | STRING
    | TRUE 
    | FALSE
    | THIS
    | NULL
    | BRACKET_OPEN expr BRACKET_CLOSE
    | ident
    | expr POINT ident
    | ident SET expr
    | expr POINT ident SET expr
    | ident BRACKET_OPEN lexpr_opt  BRACKET_CLOSE
    | expr POINT ident BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    | NEW ident BRACKET_OPEN lexpr_opt BRACKET_CLOSE
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
    /* empty */ SEMICOLON
    | expr SEMICOLON
    | type ident SEMICOLON
    | type ident SET expr SEMICOLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt SEMICOLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt SEMICOLON

    | FOR BRACKET_OPEN SEMICOLON SEMICOLON BRACKET_CLOSE stmt SEMICOLON                  
    | FOR BRACKET_OPEN SEMICOLON SEMICOLON stmt BRACKET_CLOSE stmt SEMICOLON              
    | FOR BRACKET_OPEN SEMICOLON stmt SEMICOLON BRACKET_CLOSE stmt SEMICOLON              
    | FOR BRACKET_OPEN SEMICOLON stmt SEMICOLON stmt BRACKET_CLOSE stmt SEMICOLON        
    | FOR BRACKET_OPEN stmt SEMICOLON SEMICOLON BRACKET_CLOSE stmt SEMICOLON              
    | FOR BRACKET_OPEN stmt SEMICOLON SEMICOLON stmt BRACKET_CLOSE stmt SEMICOLON         
    | FOR BRACKET_OPEN stmt SEMICOLON stmt SEMICOLON BRACKET_CLOSE stmt SEMICOLON        
    | FOR BRACKET_OPEN stmt SEMICOLON stmt SEMICOLON stmt BRACKET_CLOSE stmt SEMICOLON    

    | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE SEMICOLON
    | RETURN /*empty*/ SEMICOLON
    | RETURN expr SEMICOLON
;

params_opt:
    params
    | /* empty */
    ;

lexpr_opt:
    lexpr
    | /* empty */
    ;

expr_opt:
    expr
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