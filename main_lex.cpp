#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include <iostream>
#include <iomanip> // pour std::setw


// Fonction utilitaire pour convertir un TokenType en texte lisible
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        // --- Mots-clés ---
        case TokenType::KW_CLASS: return "CLASS";
        case TokenType::KW_BOOLEAN: return "BOOLEAN";
        case TokenType::KW_INT: return "INT";
        case TokenType::KW_PUBLIC: return "PUBLIC";
        case TokenType::KW_STATIC: return "STATIC";
        case TokenType::KW_VOID: return "VOID";
        case TokenType::KW_EXTENDS: return "EXTENDS";
        case TokenType::KW_MAIN_C: return "MAIN_C";
        case TokenType::KW_STRING_C: return "STRING_C";
        case TokenType::KW_RETURN: return "RETURN";
        case TokenType::KW_SET: return "SET";
        case TokenType::KW_NEW: return "NEW";
        case TokenType::KW_THIS: return "THIS";
        case TokenType::KW_NULL: return "NULL";
        case TokenType::KW_TRUE: return "TRUE";
        case TokenType::KW_FALSE: return "FALSE";
        case TokenType::KW_FOR: return "FOR";
        case TokenType::KW_IF: return "IF";
        case TokenType::KW_ELSE: return "ELSE";
        case TokenType::KW_INSTANCE_OF: return "INSTANCE_OF";

        // --- Symboles / opérateurs ---
        case TokenType::KW_CURLBRACKET_OPEN: return "CURLBRACKET_OPEN ({)";
        case TokenType::KW_CURLBRACKET_CLOSE: return "CURLBRACKET_CLOSE (})";
        case TokenType::KW_SEMI_COLON: return "SEMI_COLON (;)";
        case TokenType::KW_COMA: return "COMA (,)";
        case TokenType::KW_SQUBRACKET_OPEN: return "SQUBRACKET_OPEN ([)";
        case TokenType::KW_SQUBRACKET_CLOSE: return "SQUBRACKET_CLOSE (])";
        case TokenType::KW_POINT: return "POINT (.)";
        case TokenType::KW_BRACKET_OPEN: return "BRACKET_OPEN (()";
        case TokenType::KW_BRACKET_CLOSE: return "BRACKET_CLOSE ())";

        case TokenType::KW_NOT: return "NOT (!)";
        case TokenType::KW_EQUALS: return "EQUALS (=)";
        case TokenType::KW_OR: return "OR (||)";
        case TokenType::KW_AND: return "AND (&&)";
        case TokenType::KW_DIFFERENT: return "DIFFERENT (!=)";
        case TokenType::KW_SMALLER: return "SMALLER (<)";
        case TokenType::KW_SMALLER_OR_EQUAL: return "SMALLER_OR_EQUAL (<=)";
        case TokenType::KW_BIGGER: return "BIGGER (>)";
        case TokenType::KW_BIGGER_OR_EQUAL: return "BIGGER_OR_EQUAL (>=)";
        case TokenType::KW_PLUS: return "PLUS (+)";
        case TokenType::KW_MINUS: return "MINUS (-)";
        case TokenType::KW_TIMES: return "TIMES (*)";
        case TokenType::KW_DIVIDE: return "DIVIDE (/)";
        case TokenType::KW_REMAIN: return "REMAIN (%)";
        case TokenType::KW_NEGATIVE: return "NEGATIVE (-)";
        case TokenType::KW_CAST: return "CAST";

        // --- Identifiants / littéraux ---
        case TokenType::KW_IDENT: return "IDENT";
        case TokenType::KW_INTEGER: return "INTEGER";
        case TokenType::KW_STRING: return "STRING";

        // --- Spécial ---
        case TokenType::KW_MAIN: return "MAIN";
        case TokenType::KW_EOF: return "EOF";

        // --- Erreur ---
        case TokenType::KW_ERROR: return "ERROR";

        default: return "UNKNOWN";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./lexer_test <test.jura>\n";
        return 1;
    }

    Lexer lexer(argv[1]);
    Token tok;

    std::cout << std::left
              << std::setw(10) << "Ligne"
              << std::setw(25) << "Type"
              << "Lexème" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    do {
        tok = lexer.nextToken();
        std::cout << std::setw(10) << tok.line
                  << std::setw(25) << tokenTypeToString(tok.type)
                  << tok.lexeme << std::endl;
    } while (tok.type != TokenType::KW_EOF);

    return 0;
}