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
            yylval.str = strdup(t.lexeme.c_str());
            return IDENT;
        case TokenType::KW_INTEGER:
            yylval.ival = std::stoi(t.lexeme);
            return INTEGER;
        case TokenType::KW_STRING:
            yylval.str = strdup(t.lexeme.c_str());
            return STRING;

        case TokenType::KW_CLASS: return CLASS;
        case TokenType::KW_BOOLEAN: return BOOLEAN;
        case TokenType::KW_INT: return INT;
        case TokenType::KW_PUBLIC: return PUBLIC;
        case TokenType::KW_STATIC: return STATIC;
        case TokenType::KW_VOID: return VOID;
        case TokenType::KW_EXTENDS: return EXTENDS;
        case TokenType::KW_MAIN_C: return MAIN_C;
        case TokenType::KW_STRING_C: return STRING_C;
        case TokenType::KW_RETURN: return RETURN;
        case TokenType::KW_SET: return SET;
        case TokenType::KW_NEW: return NEW;
        case TokenType::KW_THIS: return THIS;
        case TokenType::KW_NULL: return NULL_TOKEN;
        case TokenType::KW_TRUE: return TRUE;
        case TokenType::KW_FALSE: return FALSE;
        case TokenType::KW_FOR: return FOR;
        case TokenType::KW_IF: return IF;
        case TokenType::KW_ELSE: return ELSE;
        case TokenType::KW_INSTANCE_OF: return INSTANCE_OF;

        case TokenType::KW_CURLBRACKET_OPEN: return CURLBRACKET_OPEN;
        case TokenType::KW_CURLBRACKET_CLOSE: return CURLBRACKET_CLOSE;
        case TokenType::KW_SEMI_COLON: return SEMI_COLON;
        case TokenType::KW_COMA: return COMA;
        case TokenType::KW_SQUBRACKET_OPEN: return SQUBRACKET_OPEN;
        case TokenType::KW_SQUBRACKET_CLOSE: return SQUBRACKET_CLOSE;
        case TokenType::KW_POINT: return POINT;
        case TokenType::KW_BRACKET_OPEN: return BRACKET_OPEN;
        case TokenType::KW_BRACKET_CLOSE: return BRACKET_CLOSE;

        case TokenType::KW_NOT: return NOT;
        case TokenType::KW_EQUALS: return EQUALS;
        case TokenType::KW_OR: return OR;
        case TokenType::KW_AND: return AND;
        case TokenType::KW_DIFFERENT: return DIFFERENT;
        case TokenType::KW_SMALLER: return SMALLER;
        case TokenType::KW_SMALLER_OR_EQUAL: return SMALLER_OR_EQUAL;
        case TokenType::KW_BIGGER: return BIGGER;
        case TokenType::KW_BIGGER_OR_EQUAL: return BIGGER_OR_EQUAL;
        case TokenType::KW_PLUS: return PLUS;
        case TokenType::KW_MINUS: return MINUS;
        case TokenType::KW_TIMES: return TIMES;
        case TokenType::KW_DIVIDE: return DIVIDE;
        case TokenType::KW_REMAIN: return REMAIN;
        case TokenType::KW_NEGATIVE: return NEGATIVE;
        case TokenType::KW_CAST: return CAST;

        case TokenType::KW_MAIN: return MAIN;
        case TokenType::KW_EOF: std::cout << "Bonjour le monde !" << std::endl; return -1 ;



        default:
            std::cerr << "Erreur lexicale à la ligne " << t.line
                      << " : '" << t.lexeme << "'" << std::endl;
            return -1;
    }
}

extern "C" void yyerror(const char* msg) {
    int line = 0;
    if (gLexer) line = gLexer->getLine();
    std::cerr << "Erreur de syntaxe à la ligne " << line << " : " << msg << std::endl;
}