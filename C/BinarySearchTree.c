#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *parent, *left, *right;
} Node;

typedef struct BST {
    Node *root;
} BST;

/* Construction functions of the Binary Search Tree (BST) and its node structure (Node) */
/* Helper function for BST creation */
BST* newBST(Node *root);
/* Helpter function for BST Node creation */
Node* newNode(int key);

/* Freeing function for the BST and its node structure */
/* Recursively frees the BST structure */
void freeBST(BST *root);
/* Recursively frees the children of the node */
void freeNodeStructure(Node *node);
/* Frees the content of the node */
void freeNode(Node *node);

/* Functions for the BST */
/* Prints the tree in order from left to right */
void inorderTreeWalk(Node *node);
/*  */
void bstRecInsert(Node *root, Node *node);
/*  */
void bstIteInsert(BST *bst, Node *node);
/*  */
void bstDeleteNode(BST *tree ,Node *node);
/* Replaces the root with the replacement node */
void bstTransplant(BST *tree, Node *root, Node *replacement);
/* Recursively seraches for a key in the BST */
Node* bstRecSearch(Node *node, int key);
/* Iteratively searches for a key in the BST */
Node *bstIteSearch(Node *node, int key);
/* Finds and returns the node with the smallest key value */
Node *bstMinimum(Node *node);
/* Finds and returns the node with the highest key value */
Node *bstMaximum(Node *node);
/*  */
Node *bstSuccessor(Node *node);
/*  */
Node *bstPredecessor(Node *node);


int main(int amount, char** input) {
    Node *root = newNode(15);
    BST *tree = newBST(root);

    bstRecInsert(tree->root, newNode(6));
    bstRecInsert(tree->root, newNode(18));
    bstRecInsert(tree->root, newNode(3));
    bstRecInsert(tree->root, newNode(7));
    bstRecInsert(tree->root, newNode(17));
    bstRecInsert(tree->root, newNode(20));
    bstRecInsert(tree->root, newNode(2));
    bstRecInsert(tree->root, newNode(4));
    bstRecInsert(tree->root, newNode(13));
    bstRecInsert(tree->root, newNode(9));

    printf("\n");
    printf("%2i\n", tree->root->left->key);
    printf("%2i\n", tree->root->left->left->key);
    printf("%2i\n", tree->root->left->left->left->key);
    printf("%2i\n", tree->root->left->left->right->key);
    printf("%2i\n", tree->root->left->right->key);
    printf("%2i\n", tree->root->left->right->right->key);
    printf("%2i\n", tree->root->left->right->right->left->key);
    printf("%2i\n", tree->root->right->key);
    printf("%2i\n", tree->root->right->left->key);
    printf("%2i\n", tree->root->right->right->key);
    printf("\n");

    printf("Successor of  6 :: %-2i\n", bstSuccessor(bstRecSearch(tree->root, 6))->key);
    printf("Successor of 13 :: %-2i\n", bstSuccessor(bstRecSearch(tree->root, 13))->key);
    printf("Predecessor of  6 :: %-2i\n", bstPredecessor(bstRecSearch(tree->root, 6))->key);
    printf("Predecessor of 13 :: %-2i\n", bstPredecessor(bstRecSearch(tree->root, 13))->key);
    printf("\n");

    printf("Inorder tree walk (BST)\n");
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("\n");

    printf("BST searches (rec. and ite.)\n");
    printf("%i\n", bstRecSearch(tree->root, 13)->key);
    printf("%i\n", bstIteSearch(tree->root, 13)->key);
    printf("%i\n", bstRecSearch(tree->root, 20)->key);
    printf("%i\n", bstIteSearch(tree->root, 20)->key);
    printf("\n");

    printf("Deleting node key 20\n");
    bstDeleteNode(tree, bstRecSearch(tree->root, 20));
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("Node key 20 %s\n", bstRecSearch(tree->root, 20) == NULL ? "NOT FOUND" : "FOUND");
    printf("Node key 20 %s\n", bstIteSearch(tree->root, 20) == NULL ? "NOT FOUND" : "FOUND");
    printf("\n");

    printf("Deleting node key 3\n");
    bstDeleteNode(tree, bstRecSearch(tree->root, 3));
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("Node key 3 %s\n", bstRecSearch(tree->root, 3) == NULL ? "NOT FOUND" : "FOUND");
    printf("Node key 3 %s\n", bstIteSearch(tree->root, 3) == NULL ? "NOT FOUND" : "FOUND");
    printf("\n");

    printf("BST min/max nodes\n");
    printf("Min of the tree :: %i\n", bstMinimum(tree->root)->key);
    printf("Max of the tree :: %i\n", bstMaximum(tree->root)->key);

    freeBST(tree);

    return 0;
}

BST* newBST(Node *root) {
    BST *bst = malloc(sizeof(BST));
    bst->root = root;
    return bst;
}

Node* newNode(int key) {
    Node *node = malloc(sizeof(Node));
    node->parent = NULL;
    node->left   = NULL;
    node->right  = NULL;
    node->key = key;
    return node;
}

void freeBST(BST *bst) {
    freeNodeStructure(bst->root);
    free(bst);
    bst = NULL;
}

void freeNodeStructure(Node *node) {
    if(node != NULL) {
        freeNodeStructure(node->left);
        freeNodeStructure(node->right);
        freeNode(node);
    }
}

void freeNode(Node *node) {
    free(node);
    node = NULL;
}

void inorderTreeWalk(Node *node) {
    if(node != NULL) {
        inorderTreeWalk(node->left);
        printf(" %i ", node->key);
        inorderTreeWalk(node->right);
    }
}

void bstRecInsert(Node *root, Node *node) {
    if(root == NULL) {
        root = node;
    } else if(node->key < root->key) {
        if(root->left == NULL) {
            root->left = node;
            node->parent = root;
        } else {
            bstRecInsert(root->left, node);
        }
    } else {
        if(root->right == NULL) {
            root->right = node;
            node->parent = root;
        } else {
            bstRecInsert(root->right, node);
        }
    }
}

void bstIteInsert(BST *bst, Node *node) {
    Node *curr = NULL,
         *parent = bst->root;
    while(parent != NULL) {
        curr = parent;
        if(node->key < parent->key) {
            parent = parent->left;
        } else {
            parent = parent->right;
        }
    }
    node->parent = curr;
    if(curr == NULL) {
        bst->root = node;
    } else if(node->key < curr->key) {
        curr->left = node;
    } else {
        curr->right = node;
    }
}

void bstDeleteNode(BST *tree, Node *node) {
    if(node->left == NULL) {
        bstTransplant(tree, node, node->right);
    } else if(node->right == NULL) {
        bstTransplant(tree, node, node->left);
    } else {
        Node *min = bstMinimum(node->right);
        if(min->parent != node) {
            bstTransplant(tree, min, min->right);
            min->right = node->right;
            min->right->parent = min;
        }
        bstTransplant(tree, node, min);
        min->left = node->left;
        min->left->parent = min;
    }
}

void bstTransplant(BST *tree, Node *root, Node *replacement) {
    if(root->parent == NULL) {
        tree->root = replacement;
    } else if (root == root->parent->left) {
        root->parent->left = replacement;
    } else {
        root->parent->right = replacement;
    }
    if(replacement != NULL) {
        replacement->parent = root->parent;
    }
}

Node* bstRecSearch(Node *node, int key) {
    if(node == NULL || node->key == key) {
        return node;
    } else if(node->key > key) {
        return bstRecSearch(node->left, key);
    } else {
        return bstRecSearch(node->right, key);
    }
}

Node *bstIteSearch(Node *node, int key) {
    while(node != NULL && node->key != key) {
        if(node->key < key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return node;
}

Node *bstMinimum(Node *node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node *bstMaximum(Node *node) {
    while(node->right != NULL) {
        node = node->right;
    }
    return node;
}

Node *bstSuccessor(Node *node) {
    if(node->right != NULL) {
        return bstMinimum(node->right);
    } else {
        Node *curr = node->parent;
        while (curr != NULL && node == curr->right)
        {
            node = curr;
            curr = curr->parent;
        }
        return curr;
    }
}

Node *bstPredecessor(Node *node) {
    if(node->left != NULL) {
        return bstMinimum(node->left);
    } else {
        Node *curr = node->parent;
        while (curr != NULL && node == curr->left)
        {
            node = curr;
            curr = curr->parent;
        }
        return curr;
    }
}