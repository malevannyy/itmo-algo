// если задача написана только у одного студента,
// то этот студент получает 3 балла, поскольку эту задачу он не списывал и не давал списывать;
//
// если задача списана ровно у двух студентов,
// то каждый из них получает по 1 утешительному баллу;
//
// если задача списана всеми тремя студентами,
// то за нее баллы не начисляются никому.

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#define K unsigned long
#define V int

class CuckooHashMap {
    static const int SIZE = 1024;

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
        return ~key << mu2 % SIZE;
    }

    Entry a[SIZE]{};

    V _get(K key) {

    }

public:

    void put(K, V) {

    };

    V get(K k) {
        auto v1 = a[f1(k)].value;
        return v1 > 0 ? v1 : a[f2(k)].value;
    };


    CuckooHashMap() = default;

    void computeInc(K key) {
        const auto &v1 = a[f1(k)].value;
        if (v1 > 0) {
            v1++;
        } else {
            ;
        }
    }
};

unsigned long read_string();

int main() {
    // 1 ≤ n ≤ 100000
    unsigned n;
    scanf("%d", &n);

    auto map = new CuckooHashMap();

    for (int i = 0; i < n; i++) {
        unsigned long key = read_string();
        map->computeInc(key);

    }


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
