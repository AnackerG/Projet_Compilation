#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ASTNode ASTNode;

// Node creation functions
ASTNode* make_node_simple(int type, const char* name);
ASTNode* make_node_int(int type, int int_val);
ASTNode* make_node_string(int type, const char* str_val);

// Node manipulation functions
void add_child(ASTNode* parent, ASTNode* child);
void set_node_name(ASTNode* node, const char* name);

// Node query functions
int get_node_type(ASTNode* node);
int node_has_children(ASTNode* node);

// Memory management
void free_node(ASTNode* node);


#ifdef __cplusplus
}
#endif