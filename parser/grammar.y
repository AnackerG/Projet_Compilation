%code requires {
#include "../AST/AST_wrapper.h"
#include "../AST/AST_types.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AST/AST_wrapper.h"
#include "../AST/AST_types.h"
#ifdef __cplusplus
extern "C" {
#endif
void yyerror(const char* msg);
int yylex(void);
char* strdup(const char*);
#ifdef __cplusplus
}
#endif
ASTNode* root = NULL;
%}

%union {
    int ival;
    char* str;
    ASTNode* node;
}


%token <str> IDENT STRING
%token <ival> INTEGER
%token CLASS CURLBRACKET_OPEN CURLBRACKET_CLOSE SEMI_COLON COMA
%token SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT PUBLIC STATIC VOID EXTENDS MAIN_C STRING_C RETURN
%token SET NEW THIS NULL_TOKEN TRUE FALSE NOT EQUALS OR AND
%token DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS MINUS TIMES DIVIDE REMAIN
%token FOR IF ELSE
%token YYEOF 0 "end"
%token MAIN


%type <node> file class_star class class_Main
%type <node> decl_star decl constructor method
%type <node> params_opt params type
%type <node> expr expr_sans_binop postfix_expr postfix_expr_sans_binop
%type <node> lexpr_opt lexpr
%type <node> stmt_star stmt expr_opt
%type <str> binop

%nonassoc LOWER_THAN_ELSE
%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS MINUS
%left ELSE
%left TIMES DIVIDE REMAIN
%right NEGATIVE NOT
%right CAST

%%

file:
    CLASS class_star class_Main {
        $$ = make_node_simple(NODE_FILE, NULL);
        add_child($$, $2);
        add_child($$, $3);
        root = $$;
    }
  ;

class_star:
    /* empty */ {
        $$ = make_node_simple(NODE_STMT, NULL);
    }
  | class_star class {
        $$ = $1;
        add_child($$, $2);
    }
  ;

class:
    IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS {
        $$ = make_node_simple(NODE_CLASS, $1);
        add_child($$, $3);
        free($1);
    }
  | IDENT EXTENDS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS {
        $$ = make_node_simple(NODE_CLASS_EXTENDS, $1);
        ASTNode* parent = make_node_simple(NODE_TYPE, $3);
        add_child($$, parent);
        add_child($$, $5);
        free($1);
        free($3);
    }
  ;

decl_star:
    /* empty */ {
        $$ = make_node_simple(NODE_STMT, NULL);
    }
  | decl_star decl {
        $$ = $1;
        add_child($$, $2);
    }
  ;

decl:
    type IDENT SEMI_COLON {
        $$ = make_node_simple(NODE_VAR_DECL, $2);
        add_child($$, $1);
        free($2);
    }
  | constructor { $$ = $1; }
  | method { $$ = $1; }
  ;

constructor:
    IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE {
        $$ = make_node_simple(NODE_CONSTRUCTOR, $1);
        add_child($$, $3);
        add_child($$, $6);
        free($1);
    }
  ;

method:
    type IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD, $2);
        add_child($$, $1);
        add_child($$, $4);
        add_child($$, $7);
        free($2);
    }
  | VOID IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD_VOID, $2);
        add_child($$, $4);
        add_child($$, $7);
        free($2);
    }
  ;

params_opt:
    /* empty */ {
        $$ = make_node_simple(NODE_STMT, NULL);
    }
  | params { $$ = $1; }
  ;

params:
    type IDENT {
        $$ = make_node_simple(NODE_STMT, NULL);
        ASTNode* param = make_node_simple(NODE_PARAM, $2);
        add_child(param, $1);
        add_child($$, param);
        free($2);
    }
  | params COMA type IDENT {
        $$ = $1;
        ASTNode* param = make_node_simple(NODE_PARAM, $4);
        add_child(param, $3);
        add_child($$, param);
        free($4);
    }
  ;

type:
    BOOLEAN { $$ = make_node_simple(NODE_TYPE, "boolean"); }
  | INT { $$ = make_node_simple(NODE_TYPE, "int"); }
  | IDENT { 
        $$ = make_node_simple(NODE_TYPE, $1);
        free($1);
    }
  | STRING_C { $$ = make_node_simple(NODE_TYPE, "string"); }
  ;

class_Main:
    MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE
    CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE {
        $$ = make_node_simple(NODE_MAIN, NULL);
        add_child($$, $14);
        free($9);
    }
  ;

expr:
    INTEGER {
        $$ = make_node_int(NODE_INTEGER, $1);
    }
  | STRING {
        $$ = make_node_string(NODE_STRING, $1);
        free($1);
    }
  | TRUE { $$ = make_node_simple(NODE_TRUE, NULL); }
  | FALSE { $$ = make_node_simple(NODE_FALSE, NULL); }
  | THIS { $$ = make_node_simple(NODE_THIS, NULL); }
  | NULL_TOKEN { $$ = make_node_simple(NODE_NULL, NULL); }
  | BRACKET_OPEN expr BRACKET_CLOSE { $$ = $2; }
  | IDENT { $$ = make_node_simple(NODE_EXPR, $1); free($1); }
  | IDENT postfix_expr {
        if (get_node_type($2) == NODE_STMT && !node_has_children($2)) {
            $$ = make_node_simple(NODE_EXPR, $1);
            free($1);
            free_node($2);
        } else {
            $$ = $2;
            set_node_name($2, $1);
            free($1);
        }
    }
    | THIS postfix_expr {
        if (get_node_type($2) == NODE_STMT && !node_has_children($2)) {
            $$ = make_node_simple(NODE_THIS, NULL);
            free_node($2);
        } else {
            $$ = $2;
        }
    }
  | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_NEW, $2);
        add_child($$, $4);
        free($2);
    }
  | NEW STRING_C BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_NEW, "String");
        add_child($$, $4);
    }
  | NOT expr {
        $$ = make_node_simple(NODE_NOT, NULL);
        add_child($$, $2);
    }
  | MINUS expr %prec NEGATIVE {
        $$ = make_node_simple(NODE_NEG, NULL);
        add_child($$, $2);
    }
  | BRACKET_OPEN type BRACKET_CLOSE expr %prec CAST {
        $$ = make_node_simple(NODE_CAST, NULL);
        add_child($$, $2);
        add_child($$, $4);
    }
  | expr_sans_binop binop expr {
        $$ = make_node_simple(NODE_BINOP, $2);
        add_child($$, $1);
        add_child($$, $3);
        free($2);
    }
  ;

expr_sans_binop:
    INTEGER { $$ = make_node_int(NODE_INTEGER, $1); }
  | STRING {
        $$ = make_node_string(NODE_STRING, $1);
        free($1);
    }
  | TRUE { $$ = make_node_simple(NODE_TRUE, NULL); }
  | FALSE { $$ = make_node_simple(NODE_FALSE, NULL); }
  | THIS { $$ = make_node_simple(NODE_THIS, NULL); }
  | NULL_TOKEN { $$ = make_node_simple(NODE_NULL, NULL); }
  | BRACKET_OPEN expr BRACKET_CLOSE { $$ = $2; }
  | IDENT postfix_expr_sans_binop {
        if (get_node_type($2) == NODE_STMT && !node_has_children($2)) {
            $$ = make_node_simple(NODE_EXPR, $1);
            free($1);
            free_node($2);
        } else {
            $$ = $2;
            set_node_name($2, $1);
            free($1);
        }
    }
  | THIS postfix_expr_sans_binop {
        if (get_node_type($2) == NODE_STMT && !node_has_children($2)) {
            $$ = make_node_simple(NODE_EXPR, "this");
            free_node($2);
        } else {
            $$ = make_node_simple(NODE_EXPR, "this");
        }
    }
  | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_NEW, $2);
        add_child($$, $4);
        free($2);
    }
  | NEW STRING_C BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_NEW, "String");
        add_child($$, $4);
    }
  | NOT expr_sans_binop {
        $$ = make_node_simple(NODE_NOT, NULL);
        add_child($$, $2);
    }
  | MINUS expr_sans_binop %prec NEGATIVE {
        $$ = make_node_simple(NODE_NEG, NULL);
        add_child($$, $2);
    }
  | BRACKET_OPEN type BRACKET_CLOSE expr_sans_binop %prec CAST {
        $$ = make_node_simple(NODE_CAST, NULL);
        add_child($$, $2);
        add_child($$, $4);
    }
  ;

postfix_expr:
    /* empty */ { $$ = make_node_simple(NODE_STMT, NULL); }
  | SET expr {
        $$ = make_node_simple(NODE_SET, NULL);
        add_child($$, $2);
    }
  | BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD_CALL, NULL);
        add_child($$, $2);
    }
  | POINT IDENT {
        $$ = make_node_simple(NODE_FIELD, NULL);
        add_child($$, make_node_string(NODE_IDENTIFIER, $2));
        free($2);
    }
  | POINT IDENT SET expr {
        $$ = make_node_simple(NODE_FIELD_SET, NULL);
        add_child($$, make_node_string(NODE_IDENTIFIER, $2));
        add_child($$, $4);
        free($2);
    }
  | POINT IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD_CALL, $2);
        add_child($$, $4);
        free($2);
    }
  | INSTANCE_OF type {
        $$ = make_node_simple(NODE_INSTANCEOF, NULL);
        add_child($$, $2);
    }
  ;

postfix_expr_sans_binop:
    /* empty */ { $$ = make_node_simple(NODE_STMT, NULL); }
  | SET expr_sans_binop {
        $$ = make_node_simple(NODE_SET, NULL);
        add_child($$, $2);
    }
  | BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD_CALL, NULL);
        add_child($$, $2);
    }
  | POINT IDENT {
        $$ = make_node_simple(NODE_FIELD, $2);
        free($2);
    }
  | POINT IDENT SET expr_sans_binop {
        $$ = make_node_simple(NODE_FIELD_SET, NULL);
        add_child($$, make_node_string(NODE_IDENTIFIER, $2));
        add_child($$, $4);
        free($2);
    }
  | POINT IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE {
        $$ = make_node_simple(NODE_METHOD_CALL, $2);
        add_child($$, $4);
        free($2);
    }
  | INSTANCE_OF type {
        $$ = make_node_simple(NODE_INSTANCEOF, NULL);
        add_child($$, $2);
    }
  ;

binop:
    EQUALS { $$ = strdup("=="); }
  | DIFFERENT { $$ = strdup("!="); }
  | SMALLER { $$ = strdup("<"); }
  | SMALLER_OR_EQUAL { $$ = strdup("<="); }
  | BIGGER { $$ = strdup(">"); }
  | BIGGER_OR_EQUAL { $$ = strdup(">="); }
  | PLUS { $$ = strdup("+"); }
  | MINUS { $$ = strdup("-"); }
  | TIMES { $$ = strdup("*"); }
  | DIVIDE { $$ = strdup("/"); }
  | REMAIN { $$ = strdup("%"); }
  | AND { $$ = strdup("&&"); }
  | OR { $$ = strdup("||"); }
  ;

lexpr_opt:
    /* empty */ { $$ = make_node_simple(NODE_STMT, NULL); }
  | lexpr { $$ = $1; }
  ;

lexpr:
    expr {
        $$ = make_node_simple(NODE_STMT, NULL);
        add_child($$, $1);
    }
  | lexpr COMA expr {
        $$ = $1;
        add_child($$, $3);
    }
  ;

stmt_star:
    /* empty */ { $$ = make_node_simple(NODE_STMT, NULL); }
  | stmt_star stmt {
        $$ = $1;
        add_child($$, $2);
    }
  ;

stmt:
    SEMI_COLON { $$ = make_node_simple(NODE_STMT_EMPTY, NULL); }
  | expr SEMI_COLON {
        $$ = make_node_simple(NODE_STMT_EXPR, NULL);
        add_child($$, $1);
    }
  | type IDENT SEMI_COLON {
        $$ = make_node_simple(NODE_VAR_DECL, $2);
        add_child($$, $1);
        free($2);
    }
  | type IDENT SET expr SEMI_COLON {
        $$ = make_node_simple(NODE_VAR_DECL_INIT, $2);
        add_child($$, $1);
        add_child($$, $4);
        free($2);
    }
  | IF BRACKET_OPEN expr BRACKET_CLOSE stmt %prec LOWER_THAN_ELSE {
        $$ = make_node_simple(NODE_IF, NULL);
        add_child($$, $3);
        add_child($$, $5);
    }
  | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt {
        $$ = make_node_simple(NODE_IF_ELSE, NULL);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
    }
  | FOR BRACKET_OPEN expr_opt SEMI_COLON expr_opt SEMI_COLON expr_opt BRACKET_CLOSE stmt {
        $$ = make_node_simple(NODE_FOR, NULL);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
        add_child($$, $9);
    }
  | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE { $$ = $2; }
  | RETURN SEMI_COLON { $$ = make_node_simple(NODE_RETURN, NULL); }
  | RETURN expr SEMI_COLON {
        $$ = make_node_simple(NODE_RETURN, NULL);
        add_child($$, $2);
    }
  ;

expr_opt:
    /* empty */ { $$ = make_node_simple(NODE_STMT, NULL); }
  | expr { $$ = $1; }
  ;

%%