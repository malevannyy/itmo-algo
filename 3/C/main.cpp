#include <cstdio>

#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "MemoryLeak"

#define K int
#define V HashSet
const int SIZE = 256;

class HashSet {
private:
    struct Node {
        K key;
        Node *next;

        explicit Node(K key) {
            this->key = key;
            this->next = nullptr;
        }

        ~Node() = default;
    };

    Node *table[SIZE];

    static inline int ix(int key) {
        return key & (SIZE - 1);
    }

public:
    HashSet() = default;

    bool contains(K key) {
        for (Node *node = table[ix(key)]; node != nullptr; node = node->next) {
            if (node->key == key) {
                return true;
            }
        }
        return false;
    }

    bool add(K key) {
        Node *prev = nullptr;
        for (Node *node = table[ix(key)];
             node != nullptr;
             prev = node, node = node->next) {
            if (node->key == key) {
                return false;
            }
        }
        auto node = new Node(key);
        if (prev != nullptr) {
            prev->next = node;
        } else {
            table[ix(key)] = node;
        }
        return true;
    }
};

class HashMap {
private:
    struct Node {
        K key;
        V *value;
        Node *next;

        Node(K key, V *value) {
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }

        ~Node() = default;
    };

    Node *table[SIZE];

    static inline int ix(int key) {
        return key & (SIZE - 1);
    }

public:
    HashMap() = default;

    int size = 0;

    void put(K key, V *value) {
        Node *prev = nullptr;
        for (Node *node = table[ix(key)];
             node != nullptr;
             prev = node, node = node->next) {
            if (node->key == key) {
                node->value = value;
            }
        }
        auto node = new Node(key, value);
        if (prev != nullptr) {
            prev->next = node;
        } else {
            table[ix(key)] = node;
        }
        size++;
    }

    V *get(K key) {
        for (Node *node = table[ix(key)]; node != nullptr; node = node->next) {
            if (node->key == key) {
                return node->value;
            }
        }
        return nullptr;
    }

    V *computeNew(K key) {
        auto v = get(key);
        if (v != nullptr) {
            return v;
        } else {
            auto nv = new V();
            put(key, nv);
            return nv;
        }
    }

    int iteratorIndex = SIZE;
    Node *iteratorNode = nullptr;

    Node *next() {
        iteratorNode = iteratorNode != nullptr ? iteratorNode->next : nullptr;
        if (iteratorNode != nullptr) {
            return iteratorNode;
        }
        for (--iteratorIndex; iteratorIndex >= 0; --iteratorIndex) {
            iteratorNode = table[iteratorIndex];
            if (iteratorNode != nullptr) {
                return iteratorNode;
            }
        }
        return nullptr;
    }
};

int main() {

    int n;
    scanf("%d", &n);
    auto map = new HashMap();
    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
        map->computeNew(h)->add(i);
    }

    int keysCount = map->size;
    K keys[keysCount];
    for (int i = 0; i < keysCount; i++) {
        keys[i] = map->next()->key;
    }

    auto count = 0;

    for (int j = 0; j < keysCount; j++) {
        for (int i = 0; i < keysCount; i++) {
            if(j == i) continue;

            int hj = keys[j];
            auto js = map->get(hj);
            int hi = keys[i];
            auto is = map->get(hi);

            printf("");
        }
    }


    printf("%d", count);
}
