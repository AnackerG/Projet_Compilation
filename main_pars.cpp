#include "lexer/Lexer.h"
#include <iostream>
Lexer* gLexer;

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