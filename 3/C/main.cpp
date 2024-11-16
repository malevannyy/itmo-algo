#include <cstdio>

#define K int
#define V int

#pragma ide diagnostic ignored "cert-err34-c"

class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node *next;

        Node(K key, V value) {
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }

        ~Node() = default;
    };

    const int SIZE = 256;
    Node *table[256];

    int hash(K key) {
        // auto h = sbox[key >> 8] << 8 | sbox[key]
        return key;
    }

    int ix(int key) {
        auto h = hash(key);
        return h & (SIZE - 1);
    }

public:
    HashMap() = default;

    V get(K key) {
        for (Node *node = table[ix(key)]; node != nullptr; node = node->next) {
            if (node->key == key) {
                return node->value;
            }
        }
        throw key;
    }

    V computeInc(K key) {
        Node *prev = nullptr;
        for (Node *node = table[ix(key)];
             node != nullptr;
             prev = node, node = node->next) {
            if (node->key == key) {
                return ++(node->value);
            }
        }
        auto node = new Node(key, 1);
        if (prev != nullptr) {
            prev->next = node;
        } else {
            table[ix(key)] = node;
        }
        return node->value;
    }
};

int main(int argc, char **argv) {

    int n;
    scanf("%d", &n);
    int a[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    HashMap map;
    auto count = 0;

    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            if (a[j] - a[i] == j - i) {
                count++;
            };
        }
    }

    printf("%d", count);
}
