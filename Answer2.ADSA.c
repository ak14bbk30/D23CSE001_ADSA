#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

typedef struct node node;

node* create_node(int data) {
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void inorder_traversal(node* current) {
    if (current == NULL) {
        return;
    } else {
        inorder_traversal(current->left);
        printf("%d ", current->data);
        inorder_traversal(current->right);
    
    }
}

void inorder_traversal_REPLACE(node* temp, int array[], int* i) {
    if (temp == NULL) {
        return;
    }

    inorder_traversal_REPLACE(temp->left, array, i);
    temp->data = array[(*i)++];
    inorder_traversal_REPLACE(temp->right, array, i);
}

void pre_order_traversal(node* temp) {
    if (temp == NULL) {
        return;
    }

    printf("%d ", temp->data);
    pre_order_traversal(temp->left);
    pre_order_traversal(temp->right);
}

int main() {
    //Input Tree In the form of Inorder Traverssal.
    int array[] = {5, 10, 12, 20, 22, 25, 28, 30, 32, 36, 40, 64};
    

    node* BST = create_node(-1);
    BST->left = create_node(-1);
    BST->left->left = create_node(-1);
    BST->left->right = create_node(-1);
    BST->left->right->left = create_node(-1);
    BST->right = create_node(-1);
    BST->right->left = create_node(-1);
    BST->right->right = create_node(-1);
    BST->right->left->left = create_node(-1);
    BST->right->left->right = create_node(-1);
    BST->right->left->right->left = create_node(-1);
    BST->right->left->left->left = create_node(-1);

    int index = 0;
    inorder_traversal_REPLACE(BST, array, &index);
    printf("Structure of the given tree is maintained \n");
    printf("Pre_order Traversal of Tree of Required Structure:  ");
    pre_order_traversal(BST);
    printf("\n");
    printf("In_order Traversal of Tree of Required Structure:  ");
    inorder_traversal(BST);

    return 0;
}
