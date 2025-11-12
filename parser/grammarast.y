%{
#include <stdio.h>
#include <stdlib.h>

// ******* 1. Déclaration anticipée de la structure *******
// Ceci doit être fait avant toute référence à ASTNode*
struct ASTNode; 

#include "../AST/AST.h" // Le chemin d'inclusion de votre AST.h

#ifdef __cplusplus
extern "C" {
#endif

void yyerror(const char* msg);
int yylex(void);

#ifdef __cplusplus
}
#endif

// Déclaration de la variable globale pour stocker la racine de l'AST
extern ASTNode* gASTRoot;

%}

%union {
    int ival;
    char* str;
    // L'union peut maintenant utiliser ASTNode* car il a été déclaré.
    ASTNode* node;
}

%token <str> IDENT STRING
%token <ival> INTEGER

%type <node> file class_star class decl_star decl constructor method params_opt params type class_Main stmt_star stmt expr expr_sans_binop postfix_expr postfix_expr_sans_binop binop lexpr_opt lexpr expr_opt

%token CLASS CURLBRACKET_OPEN CURLBRACKET_CLOSE SEMI_COLON COMA
%token SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT PUBLIC STATIC VOID EXTENDS MAIN_C STRING_C RETURN
%token SET NEW THIS NULL_TOKEN TRUE FALSE NOT EQUALS OR AND
%token DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS MINUS TIMES DIVIDE REMAIN
%token FOR IF ELSE
%token YYEOF 0 "end"
%token MAIN
%nonassoc LOWER_THAN_ELSE

%right SET
%left OR
%left AND
%left EQUALS DIFFERENT
%left SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%left PLUS MINUS
%left TIMES DIVIDE REMAIN
%right NEGATIVE NOT
%right CAST

%%
file:
    CLASS class_star class_Main YYEOF
    {
        // Crée le nœud racine du programme
        $$ = make_node(NODE_FILE);
        add_child($$, $2); // class_star
        add_child($$, $3); // class_Main
        gASTRoot = $$;
    }
    ;

class_star:
    /* empty */
    {
        $$ = make_node(NODE_CLASS_LIST);
    }
    | class_star class
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;

class:
    IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_CLASS, $1);
        add_child($$, $3);
    }
    | IDENT EXTENDS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_CLASS_EXTENDS, $1);
        ASTNode* parent_name_node = make_node(NODE_IDENTIFIER, $3);
        add_child($$, parent_name_node); 
        add_child($$, $5);
    }
    ;

decl_star:
    /* empty */
    {
        $$ = make_node(NODE_DECL_LIST);
    }
    | decl_star decl
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;

decl:
    type IDENT SEMI_COLON
    {
        $$ = make_node(NODE_VAR_DECL_ONLY, $2);
        add_child($$, $1);
    }
    | constructor
    {
        $$ = $1;
    }
    | method
    {
        $$ = $1;
    }
    ;

constructor:
    IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_CONSTRUCTOR, $1);
        add_child($$, $3);
        add_child($$, $6);
    }
    ;

method:
    type IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_METHOD, $2);
        add_child($$, $1);
        add_child($$, $4);
        add_child($$, $7);
    }
    | VOID IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_METHOD_VOID, $2);
        add_child($$, $4);
        add_child($$, $7);
    }
    ;

params_opt:
    /* empty */
    {
        $$ = make_node(NODE_PARAM_LIST);
    }
    | params
    {
        $$ = $1;
    }
    ;

params:
    type IDENT
    {
        ASTNode* param = make_node(NODE_PARAM, $2);
        add_child(param, $1);
        $$ = make_node(NODE_PARAM_LIST);
        add_child($$, param);
    }
    | params COMA type IDENT
    {
        ASTNode* param = make_node(NODE_PARAM, $4);
        add_child(param, $3);
        add_child($1, param);
        $$ = $1;
    }
    ;

type:
    BOOLEAN
    {
        $$ = make_node(NODE_TYPE, "boolean");
    }
    | INT
    {
        $$ = make_node(NODE_TYPE, "int");
    }
    | IDENT
    {
        $$ = make_node(NODE_TYPE, $1);
    }
    ;

class_Main:
    MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE
    CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_MAIN);
        ASTNode* arg_node = make_node(NODE_IDENTIFIER, $9);
        add_child($$, arg_node);
        add_child($$, $14);
    }
    ;

expr:
    INTEGER
    { $$ = make_node(NODE_INTEGER, $1); }
    | STRING
    { $$ = make_node(NODE_STRING, $1, true); }
    | TRUE
    { $$ = make_node(NODE_TRUE); }
    | FALSE
    { $$ = make_node(NODE_FALSE); }
    | THIS
    { $$ = make_node(NODE_THIS); }
    | NULL_TOKEN
    { $$ = make_node(NODE_NULL); }
    | BRACKET_OPEN expr BRACKET_CLOSE
    {
        $$ = make_node(NODE_EXPR_PAREN); // NODE_EXPR_PAREN
        add_child($$, $2);
    }
    | IDENT postfix_expr
    {
        ASTNode* id_node = make_node(NODE_IDENTIFIER, $1);
        add_child(id_node, $2);
        $$ = id_node;
    }
    | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    {
        $$ = make_node(NODE_NEW, $2);
        add_child($$, $4);
    }
    | NOT expr
    {
        $$ = make_node(NODE_NOT);
        add_child($$, $2);
    }
    | NEGATIVE expr %prec NEGATIVE
    {
        $$ = make_node(NODE_NEG);
        add_child($$, $2);
    }
    | BRACKET_OPEN type BRACKET_CLOSE expr %prec CAST
    {
        $$ = make_node(NODE_CAST);
        add_child($$, $2);
        add_child($$, $4);
    }
    | expr_sans_binop binop expr
    {
        $$ = make_node(NODE_BINOP_EXPR);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;

expr_sans_binop:
    INTEGER
    { $$ = make_node(NODE_INTEGER, $1); }
    | STRING
    { $$ = make_node(NODE_STRING, $1, true); }
    | TRUE
    { $$ = make_node(NODE_TRUE); }
    | FALSE
    { $$ = make_node(NODE_FALSE); }
    | THIS
    { $$ = make_node(NODE_THIS); }
    | NULL_TOKEN
    { $$ = make_node(NODE_NULL); }
    | BRACKET_OPEN expr BRACKET_CLOSE
    {
        $$ = make_node(NODE_EXPR_PAREN);
        add_child($$, $2);
    }
    | IDENT postfix_expr_sans_binop
    {
        ASTNode* id_node = make_node(NODE_IDENTIFIER, $1);
        add_child(id_node, $2);
        $$ = id_node;
    }
    | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    {
        $$ = make_node(NODE_NEW, $2);
        add_child($$, $4);
    }
    | NOT expr_sans_binop
    {
        $$ = make_node(NODE_NOT);
        add_child($$, $2);
    }
    | NEGATIVE expr_sans_binop %prec NEGATIVE
    {
        $$ = make_node(NODE_NEG);
        add_child($$, $2);
    }
    | BRACKET_OPEN type BRACKET_CLOSE expr_sans_binop %prec CAST
    {
        $$ = make_node(NODE_CAST);
        add_child($$, $2);
        add_child($$, $4);
    }
    ;


postfix_expr:
    /* empty */
    {
        $$ = make_node(NODE_POSTFIX_EMPTY); // NODE_POSTFIX_EMPTY
    }
    | SET expr
    {
        $$ = make_node(NODE_SET);
        add_child($$, $2);
    }
    | INSTANCE_OF type
    {
        $$ = make_node(NODE_INSTANCEOF);
        add_child($$, $2);
    }
    // Ajoutez les actions sémantiques pour les autres règles postfix_expr ici
    | BRACKET_OPEN lexpr_opt BRACKET_CLOSE
    {
        // Traitement de l'appel de méthode ou de l'accès à un tableau
        // Nécessite plus de contexte pour distinguer, mais pour l'AST :
        $$ = make_node(NODE_METHOD_CALL_OR_ARRAY); // Nouveau type NODE
        add_child($$, $2);
    }
    // ...
    ;
    
postfix_expr_sans_binop:
    /* empty */
    {
        $$ = make_node(NODE_POSTFIX_EMPTY);
    }
    | SET expr_sans_binop
    {
        $$ = make_node(NODE_SET);
        add_child($$, $2);
    }
    | INSTANCE_OF type
    {
        $$ = make_node(NODE_INSTANCEOF);
        add_child($$, $2);
    }
    // ...
    ;


binop:
    EQUALS
    { $$ = make_node(NODE_BINOP, "="); }
    | DIFFERENT
    { $$ = make_node(NODE_BINOP, "!="); }
    | SMALLER
    { $$ = make_node(NODE_BINOP, "<"); }
    | SMALLER_OR_EQUAL
    { $$ = make_node(NODE_BINOP, "<="); }
    | BIGGER
    { $$ = make_node(NODE_BINOP, ">"); }
    | BIGGER_OR_EQUAL
    { $$ = make_node(NODE_BINOP, ">="); }
    | PLUS
    { $$ = make_node(NODE_BINOP, "+"); }
    | MINUS
    { $$ = make_node(NODE_BINOP, "-"); }
    | TIMES
    { $$ = make_node(NODE_BINOP, "*"); }
    | DIVIDE
    { $$ = make_node(NODE_BINOP, "/"); }
    | REMAIN
    { $$ = make_node(NODE_BINOP, "%"); }
    | AND
    { $$ = make_node(NODE_BINOP, "&&"); }
    | OR
    { $$ = make_node(NODE_BINOP, "||"); }
    ;

lexpr_opt:
    /* empty */
    {
        $$ = make_node(NODE_EXPR_LIST);
    }
    | lexpr
    {
        $$ = $1;
    }
    ;

lexpr:
    expr
    {
        $$ = make_node(NODE_EXPR_LIST);
        add_child($$, $1);
    }
    | lexpr COMA expr
    {
        add_child($1, $3);
        $$ = $1;
    }
    ;

stmt_star:
    /* empty */
    {
        $$ = make_node(NODE_STMT_LIST);
    }
    | stmt_star stmt
    {
        add_child($1, $2);
        $$ = $1;
    }
    ;

stmt:
    SEMI_COLON
    {
        $$ = make_node(NODE_STMT_EMPTY);
    }
    | expr SEMI_COLON
    {
        $$ = make_node(NODE_STMT_EXPR);
        add_child($$, $1);
    }
    | type IDENT SEMI_COLON
    {
        $$ = make_node(NODE_VAR_DECL, $2);
        add_child($$, $1);
    }
    | type IDENT SET expr SEMI_COLON
    {
        $$ = make_node(NODE_VAR_DECL_INIT, $2);
        add_child($$, $1);
        add_child($$, $4);
    }
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt %prec LOWER_THAN_ELSE
    {
        $$ = make_node(NODE_IF);
        add_child($$, $3);
        add_child($$, $5);
    }
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt
    {
        $$ = make_node(NODE_IF_ELSE);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
    }
    | FOR BRACKET_OPEN expr_opt SEMI_COLON expr_opt SEMI_COLON expr_opt BRACKET_CLOSE stmt
    {
        $$ = make_node(NODE_FOR);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
        add_child($$, $9);
    }
    | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    {
        $$ = make_node(NODE_STMT_BLOCK); // NODE_STMT_BLOCK
        add_child($$, $2);
    }
    | RETURN SEMI_COLON
    {
        $$ = make_node(NODE_RETURN_VOID); // NODE_RETURN_VOID
    }
    | RETURN expr SEMI_COLON
    {
        $$ = make_node(NODE_RETURN_EXPR); // NODE_RETURN_EXPR
        add_child($$, $2);
    }
    ;

expr_opt:
    /* empty */
    {
        $$ = make_node(NODE_EXPR_EMPTY);
    }
    | expr
    {
        $$ = $1;
    }
    ;
%%
// Ici vous mettriez la fonction yyerror et toute autre fonction C/C++ nécessaire