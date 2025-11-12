#include "AST.h"
#include "AST_wrapper.h"
#include <cstring>

extern "C" {

ASTNode* make_node_simple(int type, const char* name) {
    return make_node(static_cast<NodeType>(type), name ? name : "");
}

ASTNode* make_node_int(int type, int int_val) {
    return make_node(static_cast<NodeType>(type), int_val);
}

ASTNode* make_node_string(int type, const char* str_val) {
    return make_node(static_cast<NodeType>(type), str_val ? str_val : "", true);
}

void add_child(ASTNode* parent, ASTNode* child) {
    if (parent && child)
        parent->children.push_back(child);
}

void set_node_name(ASTNode* node, const char* name) {
    if (node && name)
        node->name = name;
}

int get_node_type(ASTNode* node) {
    return node ? static_cast<int>(node->type) : -1;
}

int node_has_children(ASTNode* node) {
    return node && !node->children.empty();
}

void free_node(ASTNode* node) {
    if (node) {
        for (auto child : node->children) {
            free_node(child);
        }
        delete node;
    }
}

}