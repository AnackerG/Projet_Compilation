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


