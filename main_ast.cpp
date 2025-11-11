#include "lexer/Lexer.h"
#include "AST/AST.h"
#include <iostream>
Lexer* gLexer;

// pour l'instant c'est le même que celui du parseur, on modifiera après

extern "C" int yyparse();

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./rune_pars <fichier.jura>\n";
        return 1;
    }

    gLexer = new Lexer(argv[1]);
    int res = yyparse();
    delete gLexer;
    return res;
}