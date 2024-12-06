#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#define K unsigned long
#define V int

class CuckooHashMap {
    static const int SIZE = 16;

    struct Entry {
        K key;
        V value;
    };

    unsigned mu1 = 1;
    unsigned mu2 = 0;

    unsigned f1(K key) {
        return key * mu1 % SIZE;
    }

    unsigned f2(K key) {
        return (~key << mu2) % SIZE;
    }

    Entry a[SIZE]{};

public:
    CuckooHashMap() = default;

    V get(K k) {
        auto v1 = a[f1(k)].value;
        return v1 > 0 ? v1 : a[f2(k)].value;
    };

    void computeInc(K k) {
        unsigned int h1 = f1(k);
        unsigned int h2 = f2(k);
        auto &v = a[h1].value;
        v++;
    }
};

unsigned long read_string();

V verdict(V i);

const unsigned int fc = 3;
// #define fc 3

int main() {
    // 1 ≤ n ≤ 100000
    unsigned n;
    scanf("%d", &n);
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
            // prod: if (v > fc) throw v;
            cout << k << ':' << v << ' ';
            scores[j] += verdict(v);
        }
        cout << '\n';
    }

    // result out
    for (unsigned int score: scores) {
        cout << score << ' ';
    }
    cout << '\n';


}

const unsigned long magic_number = 13;

unsigned long read_string() {
    unsigned long x = 0;
    string s;
    cin >> s;
    auto size = s.size();
    unsigned long y = 1;
    for (int i = 0; i < size; i++) {
        x += y * s[i];
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
