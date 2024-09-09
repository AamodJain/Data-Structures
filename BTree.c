struct Node{ // defining the structure of a node
    int n;
    int *keys;
    int leaf;
    struct Node **c;
};

struct Btree{ // defining the structure of a B-tree
    struct Node *root;
    int t;
};

struct Node* AllocateNode(){ // function to allocate memory for a node
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->keys = NULL;
    node->c = NULL;
    return node;
}

void BTreeCreate(struct Btree *T){ // function to create a B-tree
    struct Node *x = AllocateNode();
    x->leaf = 1;
    x->n = 0;
    x->keys = (int *)malloc((2*T->t-1)*sizeof(int));
    x->c = (struct Node **)malloc((2*T->t)*sizeof(struct Node *));
    T->root = x;
}

void BTreeSplitChild(struct Btree *T , struct Node* x , int i){ // function to split a child node
    struct Node *z = AllocateNode();
    struct Node *y = x->c[i];
    z->leaf = y->leaf;
    z->n = T->t - 1;
    z->keys = (int *)malloc((2*T->t-1)*sizeof(int));
    for(int j = 0; j < T->t-1; j++){
        z->keys[j] = y->keys[j+T->t];
    }
    if(y->leaf == 0){
        z->c = (struct Node **)malloc((2*T->t)*sizeof(struct Node *));
        for(int j = 0; j < T->t; j++){
            z->c[j] = y->c[j+T->t];
        }
    }
    y->n = T->t - 1;
    for(int j = x->n; j >= i+1; j--){
        x->c[j+1] = x->c[j];
    }
    x->c[i+1] = z;
    for(int j = x->n-1; j >= i; j--){
        x->keys[j+1] = x->keys[j];
    }
    x->keys[i] = y->keys[T->t-1];
    x->n = x->n + 1;
}

void BTreeInsertNonFull(struct Btree *T , struct Node *x , int k){ // function to insert a key in a non-full node
    int i = x->n - 1;
    if(x->leaf == 1){
        while(i >= 0 && k < x->keys[i]){
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n = x->n + 1;
    }
    else{
        while(i >= 0 && k < x->keys[i]){
            i--;
        }
        i++;
        if(x->c[i]->n == 2*T->t - 1){
            BTreeSplitChild(T , x , i);
            if(k > x->keys[i]){
                i++;
            }
        }
        BTreeInsertNonFull(T , x->c[i] , k);
    }
}

void BTreeInsert(struct Btree *T , int k){ // function to insert a key in a B-tree
    struct Node *r = T->root;
    if(r->n == 2*T->t - 1){
        struct Node *s = AllocateNode();
        s->keys = (int *)malloc((2*T->t-1)*sizeof(int));
        s->c = (struct Node **)malloc((2*T->t)*sizeof(struct Node *));
        T->root = s;
        s->leaf = 0;
        s->n = 0;
        s->c[0] = r;
        BTreeSplitChild(T , s , 0);
        BTreeInsertNonFull(T , s , k);
    }
    else{
        BTreeInsertNonFull(T , r , k);
    }
}

struct Node* BTreeSearch(struct Node *x , int k){ // function to search a key in a B-tree
    int i = 0;
    while(i < x->n && k > x->keys[i]){
        i++;
    }
    if(i < x->n && k == x->keys[i]){
        return x;
    }
    else if(x->leaf == 1){
        return NULL;
    }
    else{
        return BTreeSearch(x->c[i] , k);
    }
}

int BTreeMinimum(struct Node *x){ // function to find the minimum key in a B-tree
    while(x->leaf == 0){
        x = x->c[0];
    }
    return x->keys[0];
}

void BTreeInorderTraversal(struct Node *x){ // function to traverse a B-tree in inorder
    if(x->leaf == 1){
        for(int i = 0; i < x->n; i++){
            printf("%d ",x->keys[i]);
        }
    }
    else{
        for(int i = 0; i < x->n; i++){
            BTreeInorderTraversal(x->c[i]);
            printf("%d ",x->keys[i]);
        }
        BTreeInorderTraversal(x->c[x->n]);
    }
}
