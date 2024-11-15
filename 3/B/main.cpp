#include <cstdio>

#define K int
#define V int

#pragma ide diagnostic ignored "cert-err34-c"

class HashMap {
private:
    struct Node {
        int hash;
        K key;
        V value;
        Node *next;

        explicit Node(int hash, K key, V value, Node *next = nullptr) {
            this->hash = hash;
            this->key = key;
            this->value = value;
            this->next = next;
        }

        ~Node() = default;
    };

    const int SIZE = 256;
    int size = SIZE;
    Node *table[256];

    int hash(K key) {
        // auto h = ((long) key) << (key % 13);
        return key;
    }

    int ix(int key) {
        auto h = hash(key);
        return h & (size - 1);
    }

public:
    HashMap() {

    };

    V put(K key, V value) {
        Node *prev = nullptr;
        for (Node *node = table[ix(key)];
             node != nullptr;
             prev = node, node = node->next) {
            if (node->key == key) {
                auto old = node->value;
                node->value = value;
                return old;
            }
        }
        auto node = new Node(hash(key), key, value);
        if (prev != nullptr) {
            prev->next = node;
        } else {
            table[ix(key)] = node;
        }
        return value;
    }

    V get(K key) {
        for (Node *node = table[ix(key)]; node != nullptr; node = node->next) {
            if (node->key == key) {
                return node->value;
            }
        }
        throw key;
    }

    V remove(K key) {
        for (Node *node = table[ix(key)], *prev = nullptr;
             node != nullptr;
             prev = node, node = node->next) {
            if (node->key == key) {
                auto old = node->value;
                if (prev != nullptr) {
                    prev->next = node->next;
                } else {
                    table[ix(key)] = node->next;
                }
                delete node;
                return old;
            }
        }
        throw key;
    }

    V maxValue() {
        V max = 0;
        for (int i = 0; i < size; i++) {
            for (Node *node = table[i]; node != nullptr; node = node->next) {
                if (node->value > max) {
                    max = node->value;
                };
            }
        }
        return max;
    }
};

class Group {
private:
    int _count = 0;
    int _sum = 0;
    int _max = 0;
    bool _consistent = true;
    HashMap *map = new HashMap();
public:

    Group() = default;

    void add(int key, int value) {
        map->put(key, value);
        _sum += value;
        _count++;
        if (_consistent && _max < value) {
            _max = value;
        }

    }

    void remove(int key) {
        auto value = map->remove(key);
        _sum -= value;
        _count--;
        if (value >= _max) {
            _max = map->maxValue();
        }

    }

    int max() {
        return _max;
    }

    int avg() {
        return _count == 0 ? 0 :_sum / _count;
    }
};

int main(int argc, char **argv) {

    int M, Q;
    scanf("%d", &M);
    scanf("%d", &Q);

    auto groups = new Group[M]{};

    for (int i = 0; i < Q; i++) {
        char cmd[1];
        int g;
        int key;
        int value;

        auto r = scanf("%s %d", cmd, &g);
        if (r < 2) break;
        g--;
        switch (cmd[0]) {
            case '+':
                scanf("%d %d", &key, &value);
                groups[g].add(key, value);
                break;
            case '-':
                scanf("%d", &key);
                groups[g].remove(key);
                break;
            case 'm':
                printf("%d\n", groups[g].max());
                break;
            case 'a':
                printf("%d\n", groups[g].avg());
                break;
            default:
                break;
                // nop
        }
    }
}
