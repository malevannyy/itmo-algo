#include <iostream>

using namespace std;

// bcababa
// aba

// Коммандер Ламбда негодует:
// Если поменять аргументы местами то можно в 2 раза снизить потребление памати
// А так, это унылое придётся буферизировать в памяти
// Как и требование сначала посчитать индексы а потом их вывести, ]=E

// Длина строк не превосходит 2*10^5

static const auto magic_number = 0x60;
static const int mod = INT32_MAX;
static const int k = 10;

int h(const char *, int, int);

int main() {

    auto bullshit_max = 200000;
    int bullshit[bullshit_max];
    auto bullshit_index = 0;

    string t;
    string s;
    getline(cin, t);
    getline(cin, s);
    auto sl = (int) s.length(); // 3
    auto d = (int) t.length() - sl;
    auto a = t.c_str();
    auto hs = h(s.c_str(), 0, sl);
    auto kpsl = (int) pow(k, sl - 1);
    for (int j = 0, hp = h(a, j, j + sl); j <= d; j++) {
        if (j > 0) {
            auto x = (int) (a[j + sl - 1] - magic_number);
            auto dh = (x * kpsl) % mod;
            hp = dh + (hp - (a[j - 1] - magic_number)) / k;
        }

        if (hp == hs) {
            bullshit[bullshit_index++] = j;
        }
    }

    cout << bullshit_index << endl;
    for (int index = 0; index < bullshit_index; index++) {
        cout << bullshit[index] << " ";
    }

}

int h(const char *a, int from, int to) {
    int h = 0;
    int p = 1; // = any.pow(0)
    for (auto i = from; i < to; i++) {
        auto x = (int) (a[i] - magic_number);
        h = (h + p * x) % mod;
        p = (p * k) % mod;
    }

    return h;
}
