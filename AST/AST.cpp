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

void print_node_type(NodeType type) {
    switch (type) {
        case NODE_FILE: std::cout << "NODE_FILE"; break;
        case NODE_CLASS: std::cout << "NODE_CLASS"; break;
        case NODE_CLASS_EXTENDS: std::cout << "NODE_CLASS_EXTENDS"; break;
        case NODE_MAIN: std::cout << "NODE_MAIN"; break;
        case NODE_METHOD: std::cout << "NODE_METHOD"; break;
        case NODE_METHOD_VOID: std::cout << "NODE_METHOD_VOID"; break;
        case NODE_CONSTRUCTOR: std::cout << "NODE_CONSTRUCTOR"; break;
        case NODE_STMT: std::cout << "NODE_STMT"; break;
        case NODE_STMT_EMPTY: std::cout << "NODE_STMT_EMPTY"; break;
        case NODE_STMT_EXPR: std::cout << "NODE_STMT_EXPR"; break;
        case NODE_VAR_DECL: std::cout << "NODE_VAR_DECL"; break;
        case NODE_VAR_DECL_INIT: std::cout << "NODE_VAR_DECL_INIT"; break;
        case NODE_IF: std::cout << "NODE_IF"; break;
        case NODE_IF_ELSE: std::cout << "NODE_IF_ELSE"; break;
        case NODE_FOR: std::cout << "NODE_FOR"; break;
        case NODE_RETURN: std::cout << "NODE_RETURN"; break;
        case NODE_EXPR: std::cout << "NODE_EXPR"; break;
        case NODE_TYPE: std::cout << "NODE_TYPE"; break;
        case NODE_PARAM: std::cout << "NODE_PARAM"; break;
        case NODE_TRUE: std::cout << "NODE_TRUE"; break;
        case NODE_FALSE: std::cout << "NODE_FALSE"; break;
        case NODE_THIS: std::cout << "NODE_THIS"; break;
        case NODE_NULL: std::cout << "NODE_NULL"; break;
        case NODE_INTEGER: std::cout << "NODE_INTEGER"; break;
        case NODE_STRING: std::cout << "NODE_STRING"; break;
        case NODE_FIELD: std::cout << "NODE_FIELD"; break;
        case NODE_FIELD_SET: std::cout << "NODE_FIELD_SET"; break;
        case NODE_METHOD_CALL: std::cout << "NODE_METHOD_CALL"; break;
        case NODE_SET: std::cout << "NODE_SET"; break;
        case NODE_INSTANCEOF: std::cout << "NODE_INSTANCEOF"; break;
        case NODE_NOT: std::cout << "NODE_NOT"; break;
        case NODE_NEG: std::cout << "NODE_NEG"; break;
        case NODE_CAST: std::cout << "NODE_CAST"; break;
        case NODE_BINOP: std::cout << "NODE_BINOP"; break;
        case NODE_NEW: std::cout << "NODE_NEW"; break;
        default: std::cout << "UNKNOWN_NODE_TYPE"; break;
    }
}

void print_node(ASTNode* node, int indent) {
    std::cout << std::string(indent, ' ');
    print_node_type(node->type);
    std::cout << "<";
    if(node->type == NODE_INTEGER) {
        std::cout << node->int_val;
    } else if(!node->name.empty()) {
        std::cout << node->name;
    }
    std::cout << ">\n";
    int n = node->children.size();
    for(int i = 0; i < n; i++) {
        print_node(node->children[i], indent + 2);
    }
    std::cout << "\n";
}


