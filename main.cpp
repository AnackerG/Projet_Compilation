#include "lexer/Lexer.h"
#include <iostream>
#include <iomanip> // pour std::setw

// Fonction utilitaire pour convertir un TokenType en texte lisible
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::CLASS: return "CLASS";
        case TokenType::PUBLIC: return "PUBLIC";
        case TokenType::STATIC: return "STATIC";
        case TokenType::VOID: return "VOID";
        case TokenType::INT: return "INT";
        case TokenType::BOOLEAN: return "BOOLEAN";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FOR: return "FOR";
        case TokenType::RETURN: return "RETURN";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::NULL_TOKEN: return "NULL";
        case TokenType::THIS: return "THIS";
        case TokenType::NEW: return "NEW";
        case TokenType::EXTENDS: return "EXTENDS";
        case TokenType::INSTANCEOF: return "INSTANCEOF";
        case TokenType::IDENT: return "IDENT";
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::STRING_LITERAL: return "STRING";
        case TokenType::ASSIGN: return "ASSIGN (=)";
        case TokenType::PLUS: return "PLUS (+)";
        case TokenType::MINUS: return "MINUS (-)";
        case TokenType::TIMES: return "TIMES (*)";
        case TokenType::DIV: return "DIV (/)";
        case TokenType::MOD: return "MOD (%)";
        case TokenType::EQ: return "EQ (==)";
        case TokenType::NEQ: return "NEQ (!=)";
        case TokenType::LT: return "LT (<)";
        case TokenType::LE: return "LE (<=)";
        case TokenType::GT: return "GT (>)";
        case TokenType::GE: return "GE (>=)";
        case TokenType::AND: return "AND (&&)";
        case TokenType::OR: return "OR (||)";
        case TokenType::NOT: return "NOT (!)";
        case TokenType::LBRACE: return "LBRACE ({)";
        case TokenType::RBRACE: return "RBRACE (})";
        case TokenType::LPAREN: return "LPAREN (()";
        case TokenType::RPAREN: return "RPAREN ())";
        case TokenType::SEMI: return "SEMI (;)";
        case TokenType::COMMA: return "COMMA (,)";
        case TokenType::DOT: return "DOT (.)";
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}








int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./lexer_test <fichier.jura>\n";
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
    } while (tok.type != TokenType::END_OF_FILE);

    return 0;
}
