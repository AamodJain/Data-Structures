// Structure of a node of the AVL tree
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
    int balanceFactor;
};

// Function to get the height of the tree
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to update the height and balance factor of the node
void updateHeightAndBalanceFactor(struct Node *N) {
    if (N != NULL) {
        int leftHeight = height(N->left);
        int rightHeight = height(N->right);
        N->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        N->balanceFactor = leftHeight - rightHeight;
    }
}

// R Rotation
struct Node *R_Rotation(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeightAndBalanceFactor(y);
    updateHeightAndBalanceFactor(x);

    return x;
}

// L Rotation
struct Node *L_Rotation(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeightAndBalanceFactor(x);
    updateHeightAndBalanceFactor(y);

    return y;
}

// Insert a node into the AVL tree
struct Node* AVLTree_insert(struct Node* node, int key) {
    // Perform the normal BST insertion
    if (node == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        newNode->balanceFactor = 0;
        return newNode;
    }

    if (key < node->key)
        node->left = AVLTree_insert(node->left, key);
    else if (key > node->key)
        node->right = AVLTree_insert(node->right, key);
    else
        return node; // Duplicate keys are not allowed

    // Update height and balance factor of this ancestor node
    updateHeightAndBalanceFactor(node);

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = node->balanceFactor;

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return R_Rotation(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return L_Rotation(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = L_Rotation(node->left);
        return R_Rotation(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = R_Rotation(node->right);
        return L_Rotation(node);
    }

    return node;
}

// Search for a node in the AVL tree
void AVLTree_search(struct Node* node, int key) {
    if (node == NULL) {
        printf("not present\n");
        return;
    }

    if (key < node->key)
        AVLTree_search(node->left, key);
    else if (key > node->key)
        AVLTree_search(node->right, key);
    else {
        printf("present\nBalance factor of %d in the AVL Tree is %d\nHeight of %d in the AVL tree is %d\n",key, node->balanceFactor,key, node->height-1);
    }
}

// preorder traversal of the AVL tree
void AVLTree_preorder(struct Node* node) {
    if (node == NULL)
        return;

    printf("%d ", node->key);
    AVLTree_preorder(node->left);
    AVLTree_preorder(node->right);
}

// inorder traversal of the AVL tree
void AVLTree_inorder(struct Node* node) {
    if (node == NULL)
        return;

    AVLTree_inorder(node->left);
    printf("%d ", node->key);
    AVLTree_inorder(node->right);
}

// print the preorder and the inorder traversals of the AVL tree.
void AVLTree_print(struct Node* node) {
    printf("Preorder sequence: ");
    AVLTree_preorder(node);
    printf("\n");
    printf("Inorder sequence: ");
    AVLTree_inorder(node);
    printf("\n");
}
