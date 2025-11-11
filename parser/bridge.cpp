#include "grammar.tab.h"
#include "../lexer/Lexer.h"
#include <cstring>
#include <iostream>

extern Lexer* gLexer;   // pointeur global vers le lexer
extern YYSTYPE yylval;  // fourni par Bison

extern "C" int yylex() { 
    Token t = gLexer->nextToken();

    switch (t.type) {
        case TokenType::KW_IDENT:
            std::cout << "TOKENTYPE: KW_IDENT" << std::endl;
            yylval.str = strdup(t.lexeme.c_str());
            return IDENT;

        case TokenType::KW_INTEGER:
            std::cout << "TOKENTYPE: KW_INTEGER" << std::endl;
            yylval.ival = std::stoi(t.lexeme);
            return INTEGER;

        case TokenType::KW_STRING:
            std::cout << "TOKENTYPE: KW_STRING" << std::endl;
            yylval.str = strdup(t.lexeme.c_str());
            return STRING;

        case TokenType::KW_CLASS:
            std::cout << "TOKENTYPE: KW_CLASS" << std::endl;
            return CLASS;
        case TokenType::KW_BOOLEAN:
            std::cout << "TOKENTYPE: KW_BOOLEAN" << std::endl;
            return BOOLEAN;
        case TokenType::KW_INT:
            std::cout << "TOKENTYPE: KW_INT" << std::endl;
            return INT;
        case TokenType::KW_PUBLIC:
            std::cout << "TOKENTYPE: KW_PUBLIC" << std::endl;
            return PUBLIC;
        case TokenType::KW_STATIC:
            std::cout << "TOKENTYPE: KW_STATIC" << std::endl;
            return STATIC;
        case TokenType::KW_VOID:
            std::cout << "TOKENTYPE: KW_VOID" << std::endl;
            return VOID;
        case TokenType::KW_EXTENDS:
            std::cout << "TOKENTYPE: KW_EXTENDS" << std::endl;
            return EXTENDS;
        case TokenType::KW_MAIN_C:
            std::cout << "TOKENTYPE: KW_MAIN_C" << std::endl;
            return MAIN_C;
        case TokenType::KW_STRING_C:
            std::cout << "TOKENTYPE: KW_STRING_C" << std::endl;
            return STRING_C;
        case TokenType::KW_RETURN:
            std::cout << "TOKENTYPE: KW_RETURN" << std::endl;
            return RETURN;
        case TokenType::KW_SET:
            std::cout << "TOKENTYPE: KW_SET" << std::endl;
            return SET;
        case TokenType::KW_NEW:
            std::cout << "TOKENTYPE: KW_NEW" << std::endl;
            return NEW;
        case TokenType::KW_THIS:
            std::cout << "TOKENTYPE: KW_THIS" << std::endl;
            return THIS;
        case TokenType::KW_NULL:
            std::cout << "TOKENTYPE: KW_NULL" << std::endl;
            return NULL_TOKEN;
        case TokenType::KW_TRUE:
            std::cout << "TOKENTYPE: KW_TRUE" << std::endl;
            return TRUE;
        case TokenType::KW_FALSE:
            std::cout << "TOKENTYPE: KW_FALSE" << std::endl;
            return FALSE;
        case TokenType::KW_FOR:
            std::cout << "TOKENTYPE: KW_FOR" << std::endl;
            return FOR;
        case TokenType::KW_IF:
            std::cout << "TOKENTYPE: KW_IF" << std::endl;
            return IF;
        case TokenType::KW_ELSE:
            std::cout << "TOKENTYPE: KW_ELSE" << std::endl;
            return ELSE;
        case TokenType::KW_INSTANCE_OF:
            std::cout << "TOKENTYPE: KW_INSTANCE_OF" << std::endl;
            return INSTANCE_OF;

        case TokenType::KW_CURLBRACKET_OPEN:
            std::cout << "TOKENTYPE: KW_CURLBRACKET_OPEN" << std::endl;
            return CURLBRACKET_OPEN;
        case TokenType::KW_CURLBRACKET_CLOSE:
            std::cout << "TOKENTYPE: KW_CURLBRACKET_CLOSE" << std::endl;
            return CURLBRACKET_CLOSE;
        case TokenType::KW_SEMI_COLON:
            std::cout << "TOKENTYPE: KW_SEMI_COLON" << std::endl;
            return SEMI_COLON;
        case TokenType::KW_COMA:
            std::cout << "TOKENTYPE: KW_COMA" << std::endl;
            return COMA;
        case TokenType::KW_SQUBRACKET_OPEN:
            std::cout << "TOKENTYPE: KW_SQUBRACKET_OPEN" << std::endl;
            return SQUBRACKET_OPEN;
        case TokenType::KW_SQUBRACKET_CLOSE:
            std::cout << "TOKENTYPE: KW_SQUBRACKET_CLOSE" << std::endl;
            return SQUBRACKET_CLOSE;
        case TokenType::KW_POINT:
            std::cout << "TOKENTYPE: KW_POINT" << std::endl;
            return POINT;
        case TokenType::KW_BRACKET_OPEN:
            std::cout << "TOKENTYPE: KW_BRACKET_OPEN" << std::endl;
            return BRACKET_OPEN;
        case TokenType::KW_BRACKET_CLOSE:
            std::cout << "TOKENTYPE: KW_BRACKET_CLOSE" << std::endl;
            return BRACKET_CLOSE;

        case TokenType::KW_NOT:
            std::cout << "TOKENTYPE: KW_NOT" << std::endl;
            return NOT;
        case TokenType::KW_EQUALS:
            std::cout << "TOKENTYPE: KW_EQUALS" << std::endl;
            return EQUALS;
        case TokenType::KW_OR:
            std::cout << "TOKENTYPE: KW_OR" << std::endl;
            return OR;
        case TokenType::KW_AND:
            std::cout << "TOKENTYPE: KW_AND" << std::endl;
            return AND;
        case TokenType::KW_DIFFERENT:
            std::cout << "TOKENTYPE: KW_DIFFERENT" << std::endl;
            return DIFFERENT;
        case TokenType::KW_SMALLER:
            std::cout << "TOKENTYPE: KW_SMALLER" << std::endl;
            return SMALLER;
        case TokenType::KW_SMALLER_OR_EQUAL:
            std::cout << "TOKENTYPE: KW_SMALLER_OR_EQUAL" << std::endl;
            return SMALLER_OR_EQUAL;
        case TokenType::KW_BIGGER:
            std::cout << "TOKENTYPE: KW_BIGGER" << std::endl;
            return BIGGER;
        case TokenType::KW_BIGGER_OR_EQUAL:
            std::cout << "TOKENTYPE: KW_BIGGER_OR_EQUAL" << std::endl;
            return BIGGER_OR_EQUAL;
        case TokenType::KW_PLUS:
            std::cout << "TOKENTYPE: KW_PLUS" << std::endl;
            return PLUS;
        case TokenType::KW_MINUS:
            std::cout << "TOKENTYPE: KW_MINUS" << std::endl;
            return MINUS;
        case TokenType::KW_TIMES:
            std::cout << "TOKENTYPE: KW_TIMES" << std::endl;
            return TIMES;
        case TokenType::KW_DIVIDE:
            std::cout << "TOKENTYPE: KW_DIVIDE" << std::endl;
            return DIVIDE;
        case TokenType::KW_REMAIN:
            std::cout << "TOKENTYPE: KW_REMAIN" << std::endl;
            return REMAIN;
        case TokenType::KW_NEGATIVE:
            std::cout << "TOKENTYPE: KW_NEGATIVE" << std::endl;
            return NEGATIVE;
        case TokenType::KW_CAST:
            std::cout << "TOKENTYPE: KW_CAST" << std::endl;
            return CAST;

        case TokenType::KW_MAIN:
            std::cout << "TOKENTYPE: KW_MAIN" << std::endl;
            return MAIN;
        case TokenType::KW_EOF:
            std::cout << "TOKENTYPE: KW_EOF" << std::endl;
            std::cout << "LE TEXTE A ETE LU EN ENTIER" << std::endl;
            return YYEOF;

        default:
            std::cerr << "Erreur lexicale à la ligne " << t.line
                      << " : '" << t.lexeme << "'" << std::endl;
            return -1;
    }
}


extern "C" void yyerror(const char* msg) {
    int line = 0;
    if (gLexer) line = gLexer->getLine();
    std::cerr << "Erreur de syntaxe " << line <<  "code (" << stderr << ") : " << msg << std::endl;
}