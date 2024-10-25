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

Node *insert(Node *, T);

Node *next(Node *, unsigned, unsigned);

void traverse(Node *root);

int main() {
    unsigned n;
    scanf("%d", &n);

    Node *root = nullptr;

    for (int i = 0; i < n; ++i) {
        T x;
        scanf("%d", &x);

        // fixme
        if (x < 0) break;

        root = insert(root, x);
    }

    traverse(root);

    return 0;
}

Node *insert(Node *parent, T k) {
    if (parent == nullptr) {
        return new Node(k);
    } else if (k <= parent->key) {
        parent->left = insert(parent->left, k);
        parent->left->parent = parent;
    } else {
        parent->right = insert(parent->right, k);
        parent->right->parent = parent;
    }
    return parent;
}

void traverse(Node *root) {
    unsigned level = 1;
    for (Node *node = root, *prev = nullptr;
         node != nullptr && node != prev;
         prev = node, node = next(node, level, ++level)) {
        printf("%d ", node->key);
    }
}

Node *next(Node *base, unsigned current, const unsigned target) {
    for (; base != nullptr;) {
        if (base->right != nullptr && current + 1 >= target) {
            return base->right;
        } else if (base->left != nullptr && current + 1 >= target) {
            return base->left;
        } else if (base->right != nullptr) {
            base = base->right;
            ++current;
            continue;
        } else if (base->left != nullptr) {
            base = base->left;
            ++current;
            continue;
        } else {
            auto *parent = base->parent;
            if (parent != nullptr) {
                if (parent->right == base) {
                    parent->right = nullptr;
                    base = parent;
                    --current;
                    continue;
                } else {
                    parent->left = nullptr;
                    base = parent;
                    --current;
                    continue;
                }
            } else {
                if (base->right != nullptr) {
                    base = base->right;
                    ++current;
                    continue;
                } else if (base->left != nullptr) {
                    base = base->left;
                    ++current;
                    continue;
                } else {
                    return nullptr;
                }
            }
        }
    }
    return nullptr;
}