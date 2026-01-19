#pragma once
#include "Token.h"
#include <string>
#include <fstream>
#include <unordered_map>

class Lexer {
public:
    explicit Lexer(const std::string& filename);
    Token nextToken();  // renvoie le token
    int peekChar();     // regarde le token (n'avance pas)
    int getLine() const { return line; }
    int getColumn() const { return column; }
    std::string getCurrentLine() const { return currentLineStr; }



    
private:
    std::ifstream input;
    int line;
    int column;         
    char currentChar;
    std::string currentLineStr;

    void advance();                 
    void skipWhitespaceAndComments();
    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readString();
    Token makeToken(TokenType type, const std::string& lexeme);

    static std::unordered_map<std::string, TokenType> keywords;
};
