#include <cstdio>

#define T int

struct Node {
    T key;
    Node *parent;
    Node *left;
    Node *right;

    explicit Node(T key) {
        this->key = key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node *foo(T *, unsigned, unsigned, Node *, bool);

void preorder(Node *);

int main() {
    unsigned n;
    scanf("%d", &n);

    T a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    auto root = foo(a, 0, n, nullptr, false);

    preorder(root);
}

Node *foo(T *a, unsigned from, unsigned to, Node *parent, bool right) {
    unsigned d = to - from;
    unsigned sub_root_index = from + (d - 1) / 2;
    auto key = a[sub_root_index];
    auto node = new Node(key);
    if (parent != nullptr) {
        node->parent = parent;
        if (!right) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }

    if (sub_root_index > from) {
        foo(a, from, sub_root_index, node, false);
    }
    if (++sub_root_index < to) {
        foo(a, sub_root_index, to, node, true);
    }

    return node;
}

void preorder(Node *node) {
    if (node != nullptr) {
        printf("%d ", node->key);
        preorder(node->left);
        preorder(node->right);
    }
}