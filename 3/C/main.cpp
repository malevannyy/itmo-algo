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
    int size = 0;

    static inline int ix(int key) {
        return key & (SIZE - 1);
    }

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

public:

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

long choose(int n);

long f(int i);

int main() {

    int n;
    scanf("%d", &n);
    int k = n - 1;
    auto map = new HashMap();
    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
        (*map->computeNew(h + k - i))++;
    }

    auto count = 0L;

    for (auto iterator = map->iterator();;) {
        auto node = iterator->next();
        if (node == nullptr) break;
        auto v = *node->value;
        if (v > 1) {
            count += choose(v);
        }
    }


    printf("%d", (int) count);
}

long choose(int n) {
    long f2 = f(n - 2);
    return f2 * n * (n - 1) / (2 * f2);
}


long f(int i) {
    if (i < 2) {
        return 1;
    } else if (i > 20) {
        throw i;
    } else {
        long a = 1;
        for (; i > 1; --i) {
            a *= i;
        }
        return a;
    }
}
