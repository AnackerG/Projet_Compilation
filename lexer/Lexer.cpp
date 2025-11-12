#include "Lexer.h"
#include <cctype>
#include <iostream>

std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"class", TokenType::KW_CLASS},
    {"public", TokenType::KW_PUBLIC},
    {"static", TokenType::KW_STATIC},
    {"void", TokenType::KW_VOID},
    {"int", TokenType::KW_INT},
    {"boolean", TokenType::KW_BOOLEAN},
    {"if", TokenType::KW_IF},
    {"else", TokenType::KW_ELSE},
    {"for", TokenType::KW_FOR},
    {"return", TokenType::KW_RETURN},
    {"true", TokenType::KW_TRUE},
    {"false", TokenType::KW_FALSE},
    {"null", TokenType::KW_NULL},
    {"this", TokenType::KW_THIS},
    {"new", TokenType::KW_NEW},
    {"extends", TokenType::KW_EXTENDS},
    {"instanceof", TokenType::KW_INSTANCE_OF},
    {"Main", TokenType::KW_MAIN},
    {"String", TokenType::KW_STRING_C},
    {"main", TokenType::KW_MAIN_C}, // si tu veux gérer main() spécifique
    {"set", TokenType::KW_SET}
};

Lexer::Lexer(const std::string& filename)
    : input(filename, std::ios::in), line(1), column(0), currentChar('\0') {
    if (!input) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        exit(1);
    }
    advance();
}

int Lexer::peekChar() {
    int c = input.peek();
    if (c == std::char_traits<char>::eof()) return 0;
    return c;
}

void Lexer::advance() {
    int c = input.get();
    if (c == std::char_traits<char>::eof()) {
        currentChar = '\0';
    } else {
        currentChar = static_cast<char>(c);

        if (currentChar == '\n') {
            line++;
            column = 0;
            currentLineStr.clear(); // nouvelle ligne
        } else {
            column++;
            currentLineStr.push_back(currentChar); // ajoute le caractère courant à la ligne
        }
    }
}


Token Lexer::makeToken(TokenType type, const std::string& lexeme) {
    return Token{type, lexeme, line};
}

void Lexer::skipWhitespaceAndComments() {
    while (true) {
        if (std::isspace(static_cast<unsigned char>(currentChar))) {
            advance();
        }
        else if (currentChar == '/' && peekChar() == '/') {
            while (currentChar != '\n' && currentChar != '\0') advance();
        }
        else if (currentChar == '/' && peekChar() == '*') {
            advance(); advance(); 
            bool closed = false;
            while (currentChar != '\0') {
                if (currentChar == '*' && peekChar() == '/') {
                    advance(); advance(); 
                    closed = true;
                    break;
                }
                advance();
            }
            if (!closed) {
                std::cerr << "Erreur : commentaire non fermé à la ligne " << line << std::endl;
            }
        }
        else break;
    }
}

Token Lexer::readIdentifierOrKeyword() {
    std::string lexeme;
    while (currentChar != '\0' && (std::isalnum(static_cast<unsigned char>(currentChar)) || currentChar == '_')) {
        lexeme.push_back(currentChar);
        advance();
    }
    auto it = keywords.find(lexeme);
    if (it != keywords.end()) return makeToken(it->second, lexeme);
    return makeToken(TokenType::KW_IDENT, lexeme); // identifiant
}

Token Lexer::readNumber() {
    std::string lexeme;
    while (currentChar != '\0' && std::isdigit(static_cast<unsigned char>(currentChar))) {
        lexeme.push_back(currentChar);
        advance();
    }
    return makeToken(TokenType::KW_INTEGER, lexeme);
}

Token Lexer::readString() {
    std::string lexeme;
    advance(); // "

    while (currentChar != '\0' && currentChar != '"') {
        if (currentChar == '\\') {
            advance();
            switch (currentChar) {
                case 'n': lexeme.push_back('\n'); break;
                case 't': lexeme.push_back('\t'); break;
                case 'r': lexeme.push_back('\r'); break;
                case '"': lexeme.push_back('"'); break;
                case '\\': lexeme.push_back('\\'); break;
                default: lexeme.push_back(currentChar); break;
            }
            advance();
        } else {
            lexeme.push_back(currentChar);
            advance();
        }
    }

    if (currentChar != '"') {
        std::cerr << "Erreur lexicale : chaîne non fermée (ligne " << line << ")\n";
        return makeToken(TokenType::KW_ERROR, lexeme);
    }

    advance(); // "
    return makeToken(TokenType::KW_STRING, lexeme);
}

Token Lexer::nextToken() {
    skipWhitespaceAndComments();

    if (currentChar == '\0') return makeToken(TokenType::KW_EOF, "");

    if (std::isalpha(static_cast<unsigned char>(currentChar)) || currentChar == '_') {
        return readIdentifierOrKeyword();
    }

    if (std::isdigit(static_cast<unsigned char>(currentChar))) {
        return readNumber();
    }

    if (currentChar == '"') {
        return readString();
    }

    switch (currentChar) {
        case '{': advance(); return makeToken(TokenType::KW_CURLBRACKET_OPEN, "{");
        case '}': advance(); return makeToken(TokenType::KW_CURLBRACKET_CLOSE, "}");
        case '(': advance(); return makeToken(TokenType::KW_BRACKET_OPEN, "(");
        case ')': advance(); return makeToken(TokenType::KW_BRACKET_CLOSE, ")");
        case '[': advance(); return makeToken(TokenType::KW_SQUBRACKET_OPEN, "[");
        case ']': advance(); return makeToken(TokenType::KW_SQUBRACKET_CLOSE, "]");
        case ';': advance(); return makeToken(TokenType::KW_SEMI_COLON, ";");
        case ',': advance(); return makeToken(TokenType::KW_COMA, ",");
        case '.': advance(); return makeToken(TokenType::KW_POINT, ".");
        case '+': advance(); return makeToken(TokenType::KW_PLUS, "+");
        case '-': advance(); return makeToken(TokenType::KW_MINUS, "-");
        case '*': advance(); return makeToken(TokenType::KW_TIMES, "*");
        case '/': advance(); return makeToken(TokenType::KW_DIVIDE, "/");
        case '%': advance(); return makeToken(TokenType::KW_REMAIN, "%");
        case '=':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::KW_EQUALS, "=="); }
            return makeToken(TokenType::KW_SET, "="); // assignation
        case '!':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::KW_DIFFERENT, "!="); }
            return makeToken(TokenType::KW_NOT, "!");
        case '<':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::KW_SMALLER_OR_EQUAL, "<="); }
            return makeToken(TokenType::KW_SMALLER, "<");
        case '>':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::KW_BIGGER_OR_EQUAL, ">="); }
            return makeToken(TokenType::KW_BIGGER, ">");
        case '&':
            advance();
            if (currentChar == '&') { advance(); return makeToken(TokenType::KW_AND, "&&"); }
            return makeToken(TokenType::KW_ERROR, "&");
        case '|':
            advance();
            if (currentChar == '|') { advance(); return makeToken(TokenType::KW_OR, "||"); }
            return makeToken(TokenType::KW_ERROR, "|");
        default:
            {
                std::string s(1, currentChar);
                std::cerr << "Erreur : caractère inconnu '" << currentChar
                          << "' à la ligne " << line << "\n";
                advance();
                return makeToken(TokenType::KW_ERROR, s);
            }
    }
}



