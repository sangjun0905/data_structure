#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* search(TreeNode *node, int key){
    if(node == NULL) return NULL;
    if(key == node->data) return node;
    else if(key < node->data) return search(node->left, key);
    else if(key > node->data) return search(node->right, key);
}

TreeNode* search2(TreeNode *node, int key){
    while (node != NULL){
        if(key == node->data) return node;
        else if(key < node->data) node = node->left;
        else node = node->right;
    }
    return NULL;
}
