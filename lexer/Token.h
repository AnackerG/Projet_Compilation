#pragma once
#include <string>

enum class TokenType {
    // --- Mots-clés ---
    KW_CLASS,
    KW_BOOLEAN,
    KW_INT,
    KW_PUBLIC,
    KW_STATIC,
    KW_VOID,
    KW_EXTENDS,
    KW_MAIN_C,
    KW_STRING_C,
    KW_RETURN,
    KW_SET,
    KW_NEW,
    KW_THIS,
    KW_NULL,
    KW_TRUE,
    KW_FALSE,
    KW_FOR,
    KW_IF,
    KW_ELSE,
    KW_INSTANCE_OF,

    // --- Symboles / opérateurs ---
    KW_CURLBRACKET_OPEN,
    KW_CURLBRACKET_CLOSE,
    KW_SEMI_COLON,
    KW_COMA,
    KW_SQUBRACKET_OPEN,
    KW_SQUBRACKET_CLOSE,
    KW_POINT,
    KW_BRACKET_OPEN,
    KW_BRACKET_CLOSE,

    KW_NOT,
    KW_EQUALS,
    KW_OR,
    KW_AND,
    KW_DIFFERENT,
    KW_SMALLER,
    KW_SMALLER_OR_EQUAL,
    KW_BIGGER,
    KW_BIGGER_OR_EQUAL,
    KW_PLUS,
    KW_MINUS,
    KW_TIMES,
    KW_DIVIDE,
    KW_REMAIN,
    KW_NEGATIVE,
    KW_CAST,

    // --- Identifiants / littéraux ---
    KW_IDENT,
    KW_INTEGER,
    KW_STRING,

    // --- Spécial ---
    KW_MAIN,
    KW_EOF,

    // --- Erreur ---
    KW_ERROR
};


struct Token {
    TokenType type;
    std::string lexeme;
    int line;  // numéro de ligne (pour messages d’erreurs)
};