#include "AST.h"
#include <fstream>
#include <string>

static int node_counter = 0;


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

#include <algorithm>
#include <cctype>

static std::string to_upper(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return static_cast<char>(std::toupper(c)); });
    return out;
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

std::string node_type_to_string(NodeType type) {
    switch (type) {
        case NODE_FILE: return "FILE_ROOT";
        case NODE_CLASS: return "CLASS_DECL";
        case NODE_CLASS_EXTENDS: return "CLASS_EXTENDS";
        case NODE_MAIN: return "MAIN_METHOD";
        case NODE_METHOD: return "METHOD_TYPED";
        case NODE_METHOD_VOID: return "METHOD_VOID";
        case NODE_CONSTRUCTOR: return "CONSTRUCTOR";
        case NODE_TYPE: return "TYPE";
        case NODE_PARAM: return "PARAMETER";
        case NODE_STMT: return "STATEMENT_BASE";
        case NODE_STMT_EMPTY: return "STMT_EMPTY";
        case NODE_STMT_EXPR: return "STMT_EXPR";
        case NODE_VAR_DECL: return "VAR_DECL";
        case NODE_VAR_DECL_INIT: return "VAR_DECL_INIT";
        case NODE_IF: return "IF";
        case NODE_IF_ELSE: return "IF_ELSE";
        case NODE_FOR: return "FOR_LOOP";
        case NODE_RETURN: return "RETURN_STMT";
        case NODE_EXPR: return "EXPRESSION_BASE";
        case NODE_TRUE: return "LITERAL_TRUE";
        case NODE_FALSE: return "LITERAL_FALSE";
        case NODE_THIS: return "LITERAL_THIS";
        case NODE_NULL: return "LITERAL_NULL";
        case NODE_INTEGER: return "LITERAL_INT";
        case NODE_STRING: return "LITERAL_STRING";
        case NODE_FIELD: return "FIELD_ACCESS";
        case NODE_FIELD_SET: return "FIELD_SET";
        case NODE_METHOD_CALL: return "METHOD_CALL";
        case NODE_SET: return "ASSIGNMENT";
        case NODE_INSTANCEOF: return "INSTANCEOF";
        case NODE_NOT: return "UNARY_NOT";
        case NODE_NEG: return "UNARY_NEG";
        case NODE_CAST: return "CAST";
        case NODE_BINOP: return "BINOP_TYPE"; 
        case NODE_NEW: return "NEW_OBJECT";
        default: return "UNKNOWN_NODE_TYPE";
    }
}

void write_dot_recursive(std::ofstream& file, ASTNode* node, int parent_id) {
    if (!node) return;

    int current_id = node_counter++;
    std::string label;
    
    
    if(node->type == NODE_VAR_DECL) {
        label = to_upper(node->children[0]->name) + "_DECL";
        node->children.erase(node->children.begin());
    } else if(node->type == NODE_VAR_DECL_INIT) {
        label = to_upper(node->children[0]->name) + "_DECL_INIT";
        node->children.erase(node->children.begin());
    } else {
        label = node_type_to_string(node->type);
    }
    if (!node->name.empty()) {
        if(node->type == NODE_BINOP) {
            label = node->name;
        } else {
            label += "\\nName: " + node->name;
        }
    } else if (node->int_val) {
        label += "\\nValue: " + std::to_string(node->int_val);
    } else if (!node->str_val.empty()) {
        label += "\\nValue: " + node->str_val;
    }


    file << "    node" << current_id << " [label=\"" << label << "\"];\n";

    if (parent_id != -1) {
        file << "    node" << parent_id << " -> node" << current_id << ";\n";
    }

    for (ASTNode* child : node->children) {
        write_dot_recursive(file, child, current_id);
    }
}

void generate_dot_file(ASTNode* root, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier .dot" << std::endl;
        return;
    }

    file << "digraph AST {\n";
    file << "    rankdir=TB; // Top to Bottom\n";
    file << "    node [shape=box];\n";

    node_counter = 0; 
    write_dot_recursive(file, root, -1);

    file << "}\n";
    file.close();
    std::cout << "Fichier DOT généré: " << filename << std::endl;
}