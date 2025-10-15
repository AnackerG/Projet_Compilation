#include "Lexer.h"
#include <cctype>
#include <iostream>

std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"class", TokenType::CLASS}, 
    {"public", TokenType::PUBLIC}, 
    {"static", TokenType::STATIC},
    {"void", TokenType::VOID}, 
    {"int", TokenType::INT}, 
    {"boolean", TokenType::BOOLEAN},
    {"if", TokenType::IF}, 
    {"else", TokenType::ELSE}, 
    {"for", TokenType::FOR},
    {"return", TokenType::RETURN}, 
    {"true", TokenType::TRUE}, 
    {"false", TokenType::FALSE},
    {"null", TokenType::NULL_TOKEN}, 
    {"this", TokenType::THIS}, 
    {"new", TokenType::NEW},
    {"extends", TokenType::EXTENDS}, 
    {"instanceof", TokenType::INSTANCEOF}
};



Lexer::Lexer(const std::string& filename)               //constructeur
    : input(filename, std::ios::in), line(1), column(0), currentChar('\0') {
    if (!input) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        exit(1);
    }
    advance();          // initialise currentChar
}



int Lexer::peekChar() {                                 // lecture du caractère (pas de mouvement)
    int c = input.peek();
    if (c == std::char_traits<char>::eof()) return 0;
    return c;
}



void Lexer::advance() {                                 // avance d'un caractère
    int c = input.get();
    if (c == std::char_traits<char>::eof()) {
        currentChar = '\0';
    } else {
        currentChar = static_cast<char>(c);
        if (currentChar == '\n') {
            line++;
            column = 0;
        } else {
            column++;
        }
    }
}



Token Lexer::makeToken(TokenType type, const std::string& lexeme) {     
    return Token{type, lexeme, line};
}



void Lexer::skipWhitespaceAndComments() {
    while (true) {
        if (std::isspace(static_cast<unsigned char>(currentChar))) {            // zones vides
            advance();
        }
        else if (currentChar == '/' && peekChar() == '/') {                        // Commentaires
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



Token Lexer::readIdentifierOrKeyword() {                // reconnnaitre les IDENT et les mots-clés
    std::string lexeme;
    while (currentChar != '\0' && (std::isalnum(static_cast<unsigned char>(currentChar)) || currentChar == '_')) {  //alphanumérique ou _
        lexeme.push_back(currentChar);
        advance();
    }
    auto it = keywords.find(lexeme);
    if (it != keywords.end()) return makeToken(it->second, lexeme);     //on crée le token
    return makeToken(TokenType::IDENT, lexeme);                         // si pas dans les mots-clés, c'est un identifiant
}



Token Lexer::readNumber() {                             // reconnaitre les INTEGER
    std::string lexeme;
    while (currentChar != '\0' && std::isdigit(static_cast<unsigned char>(currentChar))) {
        lexeme.push_back(currentChar);
        advance();
    }
    return makeToken(TokenType::INTEGER, lexeme);
}



Token Lexer::readString() {
    std::string lexeme;
    advance();              // " du début
    while (currentChar != '\0' && currentChar != '"') {
        if (currentChar == '\\') {
            advance();
            if (currentChar == 'n') { lexeme.push_back('\n'); }
            else if (currentChar == 't') { lexeme.push_back('\t'); }
            else if (currentChar == 'r') { lexeme.push_back('\r'); }
            else if (currentChar == '"') { lexeme.push_back('"'); }
            else if (currentChar == '\\') { lexeme.push_back('\\'); }
            else { lexeme.push_back(currentChar); }
            advance();
        } else {
            lexeme.push_back(currentChar);
            advance();
        }
    }

    if (currentChar != '"') {
        std::cerr << "Erreur lexicale : chaîne non fermée (ligne " << line << ")\n";
        return makeToken(TokenType::ERROR, lexeme);
    }

    advance(); // " de fin
    return makeToken(TokenType::STRING_LITERAL, lexeme);
}



Token Lexer::nextToken() {
    skipWhitespaceAndComments();

    if (currentChar == '\0') return makeToken(TokenType::END_OF_FILE, "");

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
        case '{': advance(); return makeToken(TokenType::LBRACE, "{");
        case '}': advance(); return makeToken(TokenType::RBRACE, "}");
        case '(': advance(); return makeToken(TokenType::LPAREN, "(");
        case ')': advance(); return makeToken(TokenType::RPAREN, ")");
        case ';': advance(); return makeToken(TokenType::SEMI, ";");
        case ',': advance(); return makeToken(TokenType::COMMA, ",");
        case '.': advance(); return makeToken(TokenType::DOT, ".");
        case '+': advance(); return makeToken(TokenType::PLUS, "+");
        case '-': advance(); return makeToken(TokenType::MINUS, "-");
        case '*': advance(); return makeToken(TokenType::TIMES, "*");
        case '%': advance(); return makeToken(TokenType::MOD, "%");
        case '=':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::EQ, "=="); }
            return makeToken(TokenType::ASSIGN, "=");
        case '!':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::NEQ, "!="); }
            return makeToken(TokenType::NOT, "!");
        case '<':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::LE, "<="); }
            return makeToken(TokenType::LT, "<");
        case '>':
            advance();
            if (currentChar == '=') { advance(); return makeToken(TokenType::GE, ">="); }
            return makeToken(TokenType::GT, ">");
        case '&':
            advance();
            if (currentChar == '&') { advance(); return makeToken(TokenType::AND, "&&"); }
            return makeToken(TokenType::ERROR, "&");
        case '|':
            advance();
            if (currentChar == '|') { advance(); return makeToken(TokenType::OR, "||"); }
            return makeToken(TokenType::ERROR, "|");
        default:
            {
                std::string s(1, currentChar);
                std::cerr << "Erreur : caractère inconnu '" << currentChar
                          << "' à la ligne " << line << "\n";
                advance();
                return makeToken(TokenType::ERROR, s);
            }
    }
}
