#include <cstdio>
#include <iostream>

using namespace std;

#define K unsigned // long
#define V int

class CuckooHashMap {
    static const int SIZE = 1024;
    static const int limit = 8;

    struct Entry {
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

    unsigned mu1 = 1;
    unsigned mu2 = 0;

    unsigned f1(K key) {
        return key * mu1 % SIZE;
    }

    unsigned f2(K key) {
        return (~key << mu2) % SIZE;
    }

    Entry *a[SIZE]{};

    Entry *bump(Entry *entry, char &fn) {
        unsigned h;
        if (fn == 1) {
            h = f1(entry->key);
            fn = 2;
        } else {
            h = f2(entry->key);
            fn = 1;
        }

        if (a[h] == nullptr) {
            a[h] = entry;
            return nullptr;
        } else {
            auto save = a[h];
            a[h] = entry;
            return save;
        }
    }

    bool cuckoo(Entry *entry, Entry *nova) {
        char fn = 2;
        auto h = f2(nova->key);
        a[h] = nova;
        for (int c = 0; c < limit; c++) {
            entry = bump(entry, fn);
            if (entry == nullptr) {
                return true;
            }
        }
        return false;
    }

    void rehash() {
        // throw "rehash";
    }

public:
    CuckooHashMap() = default;

    V get(K k) {
        auto e1 = a[f1(k)];
        auto e2 = a[f2(k)];
        if (e1 != nullptr && e1->key == k) {
            return e1->value;
        } else if (e2 != nullptr && e2->key == k) {
            return e2->value;
        } else return 0;
    };

    void computeInc(K k) {
        unsigned int h1 = f1(k);
        unsigned int h2 = f2(k);
        auto entry1 = a[h1];
        auto entry2 = a[h2];
        if (entry1 == nullptr) {
            a[h1] = new Entry(k, 1);
        } else if (entry1->key == k) {
            V &v = entry1->value;
            v++;
        } else if (entry2 == nullptr) {
            a[h2] = new Entry(k, 1);
        } else if (entry2->key == k) {
            V &v = entry2->value;
            v++;
        } else if (cuckoo(entry2, new Entry(k, 1))) {
            // ok
        } else {
            rehash();
            computeInc(k);
        }
    }
};

K read_string();

V verdict(V i);

const unsigned int fc = 3;

int main() {

    // 1 ≤ n ≤ 100000
    unsigned n;
    scanf("%d", &n);
    getchar();
    auto map = new CuckooHashMap();

    K friends[fc][n];

    // collect
    for (int j = 0; j < fc; j++) {
        for (int i = 0; i < n; i++) {
            unsigned long key = read_string();
            friends[j][i] = key;
            map->computeInc(key);
        }
    }

    V scores[fc]{};

    // manna giving
    for (int j = 0; j < fc; j++) {
        for (int i = 0; i < n; i++) {
            K k = friends[j][i];
            V v = map->get(k);
            // cout << k << ':' << v << ' ';
            scores[j] += verdict(v);
        }
        // cout << '\n';
    }

    // result out
    for (unsigned int score: scores) {
        cout << score << ' ';
    }
}

const unsigned long magic_number = 13;

K read_string() {
    unsigned long x = 0;
    int c;
    unsigned long y = 1;
    for (;;) {
        c = getchar();
        if (c < 0 || c == ' ' || c == '\n') break;
        x += y * c;
        y *= magic_number;
    }

    return x;
}

V verdict(V v) {
    switch (v) {
        case 1:
            return 3;
        case 2:
            return 1;
        default:
            return 0;
    };
}
