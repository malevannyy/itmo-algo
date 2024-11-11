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

class Tree {
private:
    Node *root;

    static bool exists(Node *node, T key) {
        if (node == nullptr)
            return false;

        return node->key == key ||
               key < node->key && exists(node->left, key) ||
               key > node->key && exists(node->right, key);
    }

public:
    void insert(T key) {
        Node *parent = nullptr;
        for (Node *i = root;
             i != nullptr;
             parent = i, i = key < i->key ? i->left : i->right);
        if (parent == nullptr) {
            root = new Node(key);
        } else if (key < parent->key) {
            parent->left = new Node(key);
            parent->left->parent = parent;
        } else if (key > parent->key) {
            parent->right = new Node(key);
            parent->right->parent = parent;
        }
    }

    void del(T key) {};

    bool exists(T key) {
        return exists(root, key);
    };

    T next(T key) {
        Node *node = root;
        for (Node *i = root;
             i != nullptr;
             node = i, i = key < i->key ? i->left : i->right);
    };

    T prev(T key) {
        return 0;
    };
};


int main() {

    auto tree = new Tree();

    char cmd[16];
    T arg;
    for (int i = 0; i < 100; ++i) {
        auto r = scanf("%s %d", cmd, &arg);
        if (r < 0) break;

        switch (cmd[0]) {
            case 'i':
                tree->insert(arg);
                break;
            case 'd':
                tree->del(arg);
                break;
            case 'e':
                printf("%s\n", tree->exists(arg) ? "true" : "false");
                break;
            case 'n':
                printf("%d\n", tree->next(arg));
                break;
            case 'p':
                printf("%d\n", tree->prev(arg));
                break;
            default:
                break;
        }

    }


}