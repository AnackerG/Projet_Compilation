#include "AST.h"

ASTNode* make_node(NodeType type, const std::string& name) {
    ASTNode* node = new ASTNode();
    node->type = type;
    node->name = name;
    return node;
}

ASTNode* make_node(NodeType type, int int_val) {
    ASTNode* node = new ASTNode();
    node->type = type;
    node->int_val = int_val;
    return node;
}

ASTNode* make_node(NodeType type, const std::string& str_val, bool) {
    ASTNode* node = new ASTNode();
    node->type = type;
    node->str_val = str_val;
    return node;
}


void add_child(ASTNode* parent, ASTNode* child) {
    if (parent && child)
        parent->children.push_back(child);
}

