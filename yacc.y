%{
/* C declarations (included in the generated parser file) */
#include <stdio.h>
#include <stdlib.h>
%}

/* Bison declarations */
%token CLASS
%token CHEVRON_OPEN CHEVRON_CLOSE SEMI_COLON COMA SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT
%token PUBLIC STATIC VOID EXTENDS
%token SET
%token NEW THIS
%token NULL EOF
%token NOT EQUALS OR AND DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS LESS MULTIPLY DIVISION REMAIN NEGATIVE NEGATE CAST


/* Operator precedence and associativity (optional but common) */
%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS LESS
%left MULTIPLY DIVISION REMAIN
%left NEGATE NOT CAST
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
    CLASS ident CHEVRON_OPEN decl_star CHEVRON_CLOSE
    | CLASS ident EXTENDS ident CHEVRON_OPEN decl_star CHEVRON_CLOSE
    ;

decl:
    type ident SEMI_COLON 
    | constructor〉
    | method
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


