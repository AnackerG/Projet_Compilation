#pragma once
#include <string>



enum class TokenType {
    // Mots-clés
    CLASS, PUBLIC, STATIC, VOID, INT, BOOLEAN, IF, ELSE, FOR, RETURN,
    TRUE, FALSE, NULL_TOKEN, THIS, NEW, EXTENDS, INSTANCEOF,

    // Symboles
    LBRACE, RBRACE, LPAREN, RPAREN, SEMI, COMMA, DOT,
    ASSIGN, PLUS, MINUS, TIMES, DIV, MOD,
    EQ, NEQ, LT, LE, GT, GE,
    AND, OR, NOT,

    // Identifiants 
    IDENT, INTEGER, STRING_LITERAL,

    END_OF_FILE, ERROR
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;            //pour les erreurs
};
