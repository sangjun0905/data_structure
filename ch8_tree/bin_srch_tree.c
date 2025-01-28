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

TreeNode *new_node(int item){
    TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode *node, int key){
    if(node == NULL) return new_node(key);

    if(key < node->data){
        node->left = insert_node(node->left, key);
    }
    else if(key > node->data){
        node->right = insert_node(node->right, key);
    }
    return node;
}

TreeNode* min_value_node(TreeNode *node){
    TreeNode *current = node;

    while(current->left != NULL) current = current->left;

    return current;
}

TreeNode *delete_node(TreeNode *root, int key){
    if(root == NULL) return root;
    if(key < root->data) root->left = delete_node(root->left, key);
    else if( key > root->data) root->right = delete_node(root->right, key);
    else {
        if(root->left == NULL){
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        TreeNode *temp = min_value_node(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

void inorder(TreeNode *root){
    if(root){
        inorder(root->left);
        printf("[%d] ", root->data);
        inorder(root->right);
    }
}


int main(){
    TreeNode *root = NULL;
    TreeNode *tmp = NULL;
    root = insert_node(root, 30);
    root = insert_node(root, 70);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);

    delete_node(root, 30);
    
    printf("이진 탐색 트리 중위 순회 결과 \n");
    inorder(root);
    printf("\n\n\n");
    if(search(root, 30) != NULL) printf("이진트리에 30 존재");
    else printf("이진트리에 30 미존재");
    return 0;

}