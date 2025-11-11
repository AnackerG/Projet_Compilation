#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

enum NodeType {
    NODE_FILE,
    NODE_CLASS,
    NODE_CLASS_EXTENDS,
    NODE_MAIN,
    NODE_METHOD,
    NODE_METHOD_VOID,
    NODE_CONSTRUCTOR,
    NODE_STMT,
    NODE_STMT_EMPTY,
    NODE_STMT_EXPR,
    NODE_VAR_DECL,
    NODE_VAR_DECL_INIT,
    NODE_IF,
    NODE_IF_ELSE,
    NODE_FOR,
    NODE_RETURN,
    NODE_EXPR,
    NODE_TYPE,
    NODE_PARAM,
    NODE_TRUE,
    NODE_FALSE,
    NODE_THIS,
    NODE_NULL,
    NODE_INTEGER,
    NODE_STRING,
    NODE_FIELD,
    NODE_FIELD_SET,
    NODE_METHOD_CALL,
    NODE_SET,
    NODE_INSTANCEOF,
    NODE_NOT,
    NODE_NEG,
    NODE_CAST,
    NODE_BINOP,
    NODE_NEW
};


struct ASTNode {
    NodeType type;
    std::string name;               
    int int_val = 0;                
    std::string str_val;            
    std::vector<ASTNode*> children; 
};

ASTNode* make_node(NodeType type, const std::string& name = "");                    // pour le reste
ASTNode* make_node(NodeType type, int int_val);                                     // pour une constante
ASTNode* make_node(NodeType type, const std::string& str_val, bool is_string);      // pour une chaine
void add_child(ASTNode* parent, ASTNode* child);


//void check_semantics(ASTNode* node);      à faire après avoir l'ast

