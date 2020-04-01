#include <stdio.h>
#include <stdlib.h>

/* The structure of a node used with a Binary Search Tree (BST) */
typedef struct Node {
    int key;
    struct Node *parent, *left, *right;
} Node;

/* The structure of a Binary Search Tree (BST) */
typedef struct BST {
    Node *root;
} BST;

/* Helper function for BST creation */
BST* newBST(Node *root);
/* Helpter function for BST Node creation */
Node* newNode(int key);

/* Recursively frees the BST structure */
void freeBST(BST *root);
/* Recursively frees the children of the node */
void freeNodeStructure(Node *node);
/* Frees the content of the node */
void freeNode(Node *node);

/* Prints the tree in order from left to right */
void inorderTreeWalk(Node *node);
/* Traverses the tree in order from the smallest key to the largest. The action is performed with each node in same order. */
void inorderTreeTraversal(Node *node, void (*action)(Node*));
/* Prints a node key by using printf */
void printNode(Node *node);
/* Recursively insert a node into the in the tree with the root */
void bstRecInsert(Node *root, Node *node);
/* Iteratively insert a node into the in the tree with the root */
void bstIteInsert(BST *bst, Node *node);
/* Deletes/Removes a node from a tree */
void bstDeleteNode(BST *tree, Node *node);
/* Deletes/Removes a key from a tree */
void bstRemoveKey(BST *tree, int key);
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
/* Returns the node with the smallest key greater than the key of input node */
Node *bstSuccessor(Node *node);
/* the node with the greatest key smaller than the key of input node */
Node *bstPredecessor(Node *node);
/* Returns TRUE (!0) if the bst is a valid bst */
void isValidBST(Node *node);
/* Checks if the root of the tree and its childrens is inside the range of min and max. Returns TRUE if so. */
int isValidBSTHelper(Node *node, int min, int max);

int main(int amount, char** input) {
    Node *root = newNode(15);
    BST *tree = newBST(root);

    /* Tests */
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

    printf("Tree walk as from the ALG BST slides from left to right and from bottom to up\n");
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

    printf("Inorder tree walk (BST)\n");
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("Successor of  6 :: %-2i\n", bstSuccessor(bstRecSearch(tree->root, 6))->key);
    printf("Successor of 13 :: %-2i\n", bstSuccessor(bstRecSearch(tree->root, 13))->key);
    printf("Predecessor of  6 :: %-2i\n", bstPredecessor(bstRecSearch(tree->root, 6))->key);
    printf("Predecessor of 13 :: %-2i\n", bstPredecessor(bstRecSearch(tree->root, 13))->key);
    printf("\n");

    printf("Inorder tree walk (BST)\n");
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("BST searches recursive (Rec) and iterative (Ite)\n");
    printf("Rec. %i\n", bstRecSearch(tree->root, 13)->key);
    printf("Ite. %i\n", bstIteSearch(tree->root, 13)->key);
    printf("Rec. %i\n", bstRecSearch(tree->root, 20)->key);
    printf("Ite. %i\n", bstIteSearch(tree->root, 20)->key);
    printf("\n");

    printf("Deleting node key 20\n");
    bstDeleteNode(tree, bstRecSearch(tree->root, 20));
    printf("Inorder tree walk (BST)\n");
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("Node key 20 %s\n", bstRecSearch(tree->root, 20) == NULL ? "NOT FOUND" : "FOUND");
    printf("Node key 20 %s\n", bstIteSearch(tree->root, 20) == NULL ? "NOT FOUND" : "FOUND");
    printf("\n");

    printf("Deleting node key 3\n");
    bstDeleteNode(tree, bstRecSearch(tree->root, 3));
    printf("Inorder tree walk (BST)\n");
    inorderTreeWalk(tree->root);
    printf("\n");
    printf("Node key 3 %s\n", bstRecSearch(tree->root, 3) == NULL ? "NOT FOUND" : "FOUND");
    printf("Node key 3 %s\n", bstIteSearch(tree->root, 3) == NULL ? "NOT FOUND" : "FOUND");
    printf("\n");

    printf("BST min/max nodes\n");
    printf("Min of the tree :: %i\n", bstMinimum(tree->root)->key);
    printf("Max of the tree :: %i\n", bstMaximum(tree->root)->key);

    /* END TESTS */

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
    inorderTreeTraversal(node, printNode);
}

void inorderTreeTraversal(Node *node, void (*action)(Node*)) {
    if(node != NULL) {
        inorderTreeTraversal(node->left, action);
        action(node);
        inorderTreeTraversal(node->right, action);
    }
}

void printNode(Node *node) {
    printf("%i\n", node->key);
}

void bstRecInsert(Node *root, Node *node) {
    /* Inserts the node as a new leaf */
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
    /* Inserts the node as a new leaf */
    Node *curr = NULL,
         *parent = bst->root;
    /* Find the parent to the leaf to set (from NULL) */
    while(parent != NULL) {
        curr = parent;
        if(node->key < parent->key) {
            parent = parent->left;
        } else {
            parent = parent->right;
        }
    }
    /* Place the node on the correct child of the parent node */
    node->parent = curr;
    if(curr == NULL) {
        bst->root = node;
    } else if(node->key < curr->key) {
        curr->left = node;
    } else {
        curr->right = node;
    }
}

void bstRemoveKey(BST *tree, int key) {
    /* Can be changes to the Iteratively bst search */
    bstDeleteNode(tree, bstRecSearch(tree->root, key));
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
    /* The key of the left child is always less than the parent's and leafs are NULL */
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node *bstMaximum(Node *node) {
    /* The key of the right child is always greater than the parent's and leafs are NULL  */
    while(node->right != NULL) {
        node = node->right;
    }
    return node;
}

Node *bstSuccessor(Node *node) {
    if(node->right != NULL) {
        /* Since the key of the right child is always greater than the parent then the minimum of the sub-tree must be the Successor */
        return bstMinimum(node->right);
    } else {
        Node *curr = node->parent;
        while (curr != NULL && node == curr->right) {
            /* The node is not the root of the tree
             * The Successor must then be the first node where the node is not in the right sub-tree */
            node = curr;
            curr = curr->parent;
        }
        return curr;
    }
}

Node *bstPredecessor(Node *node) {
    if(node->left != NULL) {
        /* Since the key of the left child is always less than the parent then the minimum of the sub-tree must be the Successor */
        return bstMinimum(node->left);
    } else {
        Node *curr = node->parent;
        while (curr != NULL && node == curr->left) {
            /* The node is not the root of the tree
             * The Successor must then be the first node where the node is not in the right left-tree */
            node = curr;
            curr = curr->parent;
        }
        return curr;
    }
}

void isValidBST(Node *node) {
    /* BST property: The left child of x has a key less than x's whilst the right child key is greater than x's */
    return isValidBST(node, node->key - 1, node->key + 1);
}

int isValidBSTHelper(Node *node, int min, int max) {
    if(node == NULL) {
        return 1;
    }

    if(node->key <= min || node->key >= max) {
        return 0;
    }

    /* The bounds of min and max +-1 because all values in a BST are distinct and the bounds are including when comparing 
     * Bounds are used for some trees where you can get false positives because insertion was not done correctly */
    return isValidBSTHelper(node->left,  min, node->key - 1) &&
           isValidBSTHelper(node->right, node->key + 1, max);
}