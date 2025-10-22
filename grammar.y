%token CLASS CURLBRACKET_OPEN CURLBRACKET_CLOSE SEMI_COLON COMA
%token SQUBRACKET_OPEN SQUBRACKET_CLOSE POINT BRACKET_OPEN BRACKET_CLOSE
%token BOOLEAN INT PUBLIC STATIC VOID EXTENDS MAIN_C STRING_C RETURN
%token SET IDENT NEW THIS NULL TRUE FALSE NOT EQUALS OR AND
%token DIFFERENT SMALLER SMALLER_OR_EQUAL BIGGER BIGGER_OR_EQUAL INSTANCE_OF
%token PLUS MINUS TIMES DIVIDE REMAIN
%token FOR IF ELSE INTEGER STRING
%token EOF
%token MAIN
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
    CLASS class_star class_Main EOF
  ;

class_star:
    /* empty */
  | class_star class
  ;

class:
    IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS
  | IDENT EXTENDS IDENT CURLBRACKET_OPEN decl_star CURLBRACKET_CLOSE CLASS
  ;

decl_star:
    /* empty */
  | decl_star decl
  ;

decl:
    type IDENT SEMI_COLON 
  | constructor
  | method
  ;

constructor:
    IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
  ;

method:
    type IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
  | VOID IDENT BRACKET_OPEN params_opt BRACKET_CLOSE CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
  ;

params_opt:
    /* empty */
  | params
  ;

params:
    type IDENT
  | params COMA type IDENT
  ;

type:
    BOOLEAN
  | INT
  | IDENT
  ;

class_Main:
    MAIN CURLBRACKET_OPEN PUBLIC STATIC VOID MAIN_C BRACKET_OPEN STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE BRACKET_CLOSE
    CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE CURLBRACKET_CLOSE
  ;

expr:
    INTEGER
  | STRING
  | TRUE
  | FALSE
  | THIS
  | NULL
  | BRACKET_OPEN expr BRACKET_CLOSE
  | IDENT postfix_expr
  | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
  | NOT expr
  | NEGATIVE expr            %prec NEGATIVE
  | BRACKET_OPEN type BRACKET_CLOSE expr  %prec CAST
  | expr_sans_binop binop expr
  ;

expr_sans_binop:
    INTEGER
  | STRING
  | TRUE
  | FALSE
  | THIS
  | NULL
  | BRACKET_OPEN expr BRACKET_CLOSE
  | IDENT postfix_expr
  | NEW IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
  | NOT expr
  | NEGATIVE expr            %prec NEGATIVE
  | BRACKET_OPEN type BRACKET_CLOSE expr  %prec CAST
  ;

postfix_expr:
    /* empty */
  | SET expr
  | BRACKET_OPEN lexpr_opt BRACKET_CLOSE
  | POINT IDENT
  | POINT IDENT SET expr
  | POINT IDENT BRACKET_OPEN lexpr_opt BRACKET_CLOSE
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

lexpr_opt:
    /* empty */
  | lexpr
  ;

lexpr:
    expr
  | lexpr COMA expr
  ;

stmt_star:
    /* empty */
  | stmt_star stmt
  ;

stmt:
      SEMI_COLON
    | expr SEMI_COLON
    | type IDENT SEMI_COLON
    | type IDENT SET expr SEMI_COLON
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt %prec LOWER_THAN_ELSE
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt
    | FOR BRACKET_OPEN expr_opt SEMI_COLON expr_opt SEMI_COLON expr_opt BRACKET_CLOSE stmt
    | CURLBRACKET_OPEN stmt_star CURLBRACKET_CLOSE
    | RETURN SEMI_COLON
    | RETURN expr SEMI_COLON
  ;

expr_opt:
    /* empty */
  | expr
  ;
%%
