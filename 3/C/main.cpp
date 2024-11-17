#include <cstdio>

#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "MemoryLeak"

#define K int
#define V int
const int SIZE = 256;

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

    Node *table[SIZE];
    int size = 0;

    static inline int ix(int key) {
        return key & (SIZE - 1);
    }

    void put(K key, V value) {
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

public:

    Node *find(K key) {
        for (Node *node = table[ix(key)]; node != nullptr; node = node->next) {
            if (node->key == key) {
                return node;
            }
        }
        return nullptr;
    }

    void computeNewOrIncrement(K key) {
        auto node = find(key);
        if (node != nullptr) {
            node->value++;
        } else {
            put(key, 1);
        }
    }

    class Iterator {
    private:
        HashMap *map;
        int index = -1;
        Node *node = nullptr;
    public:
        explicit Iterator(HashMap *map) {
            this->map = map;
        }

        Node *next() {
            node = node != nullptr ? node->next : nullptr;
            if (node != nullptr) {
                return node;
            }
            for (++index; index < SIZE; index++) {
                node = map->table[index];
                if (node != nullptr) {
                    return node;
                }
            }
            return nullptr;
        }
    };

    Iterator *iterator() {
        return new Iterator(this);
    }
};

int main() {

    int n;
    scanf("%d", &n);
    auto map = new HashMap();
    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
        map->computeNewOrIncrement(h - i);
    }

    auto count = 0L;

    for (auto iterator = map->iterator();;) {
        auto node = iterator->next();
        if (node == nullptr) break;
        auto v = node->value;
        if (v > 1) {
            count += v * (v - 1) / 2;
        }
    }


    printf("%d", (int) count);
}
