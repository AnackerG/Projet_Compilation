#include "lexer/Lexer.h"
#include "AST/AST.h"
#include <iostream>
Lexer* gLexer;

// pour l'instant c'est le même que celui du parseur, on modifiera après

extern "C" int yyparse();
extern ASTNode *root;

int main(int argc, char** argv) {


    gLexer = new Lexer(argv[1]);
    int res = yyparse();
    print_node(root);
    generate_dot_file(root);
    delete gLexer;
    return res;
}