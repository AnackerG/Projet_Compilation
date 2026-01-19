#pragma once
#include "AST_types.h"
#include <string>
#include <vector>
#include <iostream>

struct ASTNode {
    NodeType type;
    std::string name;               
    int int_val = 0;                
    std::string str_val;            
    std::vector<ASTNode*> children; 
};

ASTNode* make_node(NodeType type, const std::string& name = "");
ASTNode* make_node(NodeType type, int int_val);
ASTNode* make_node(NodeType type, const std::string& str_val, bool is_string);
void print_node(ASTNode* node, int indent = 0);
std::string node_type_to_string(NodeType type);
void write_dot_recursive(std::ofstream& file, ASTNode* node, int parent_id);
void generate_dot_file(ASTNode* root, const std::string& filename = "ast.dot");


