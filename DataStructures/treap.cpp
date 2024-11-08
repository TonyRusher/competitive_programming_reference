/*-----Treap-----*/
struct Node {
    int key, priority, value;
    Node *left, *right;
    Node(int key, int priority)
        : key(key), priority(priority), value(key), left(NULL), right(NULL) {}
};
// modify this funciton depending on the query that you want
void update(Node *T) {
    if (T) {
        T->value = T->key;
        if (T->left)
            T->value += T->left->value;
        if (T->right)
            T->value += T->right->value;
    }
}
// returns the root of the union of treaps T1 and T2
Node *merge(Node *T1, Node *T2) {
    if (T1 == NULL) return T2;
    if (T2 == NULL) return T1;
    if (T1->priority > T2->priority) {
        T1->right = merge(T1->right, T2);
        update(T1); return T1;
    } else {
        T2->left = merge(T1, T2->left);
        update(T2); return T2;
    }
}

// returns the roots the division of the treap T with parameter x
pair<Node *, Node *> split(Node *T, int x) {
    if (T == NULL) return {NULL, NULL};
    Node *T1, *T2;
    if (T->key < x) {
        tie(T1, T2) = split(T->right, x);
        T->right = T1;
        update(T2); update(T);
        return {T, T2};
    } else {
        tie(T1, T2) = split(T->left, x);
        T->left = T2;
        update(T1); update(T);
        return {T1, T};
    }
}

// seed to generate random numbers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// generates random numbers
uniform_int_distribution<> dis(numeric_limits<int>::min(),
                               numeric_limits<int>::max());

// inserts a new node with key = x in the treap T, returns the new root
Node *insert(Node *T, int x) {
    Node *TN = new Node(x, dis(rng));
    Node *L, *R;
    tie(L, R) = split(T, x);
    TN = merge(L, TN); TN = merge(TN, R);
    return TN;
}
// returns a treap with all the elements in a
Node *create(vi &a) {
    Node *T = NULL;
    forn(i, (int)a.size()) T = insert(T, a[i]);
    return T;
}
// erases the key x from the treap T
Node *erase(Node *T, int x) {
    Node *L, *R, *AUX;
    tie(L, R) = split(T, x);
    tie(AUX, R) = split(R, x + 1);
    return merge(L, R);
}
// returns the sum of all the keys in te range [l,r]
int query(Node **T, int l, int r) {
    Node *L, *X, *R;
    tie(L, X) = split(*T, l);
    tie(X, R) = split(X, r + 1);
    int ans = (X) ? X->value : 0;
    X = merge(L, X); *T = merge(X, R);
    return ans;
}

// returns the k-th node of the sorted nodes in the treap
Node *findKth(Node *T, int k) {
    if (T == NULL) return NULL;
    int aux = T->left ? T->left->value : 0;
    if (aux >= k) return findKth(T->left, k);
    else if (aux + 1 == k) return T;
    else return findKth(T->right, k - aux - 1);
}
