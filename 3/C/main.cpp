#include <cstdio>
#include <iostream>

using namespace std;

#pragma ide diagnostic ignored "cert-err34-foo"

const auto m = 8u; // 100000
const auto magic_number = 3u;
const auto magic_mask = (1u << magic_number) - 1;
const auto number = 1u << magic_number;

unsigned a[number]{};

unsigned foo(unsigned);

int main() {
    unsigned n;
    unsigned shift = 1;
    unsigned count = 0;
    unsigned old_imagine;
    scanf("%d", &n);
    for (; shift < n; shift <<= 1);
    cout << "  3   5   1   4   6   6   3   5   1   3   5   5   6   5   1   4   6   6\n";
    // cout << " 20  21  16  18  19  18  18  15  10  12  13  12   8   9   4   6   7   6\n";
    cout << " 20  21  16  18  19  18  14  15  10  11  12  11  11   9   4   6   7   6\n";

    for (unsigned i = n; i > 0; i--) {
        unsigned hi;
        scanf("%d", &hi);
        auto x = hi + i - 1;

        // cout << " " << x << " ";cout.flush();

        auto imagine = x / m;
        auto real = x % m;

        cout << imagine << '|' << real << " ";cout.flush();

        old_imagine = a[real] >> magic_number;

        if (imagine == old_imagine) {
            a[real]++;
        } else {
            count = +foo(a[real] & magic_mask);
            a[real] = (imagine << magic_number) + 1;
        }
    }

    for (unsigned ic: a) {
        auto imagine = ic >> magic_number;
        if (imagine == old_imagine) {
            count += foo(ic & magic_mask);
        }
    }

    printf("\n");
    printf("%u", count);
}

unsigned foo(unsigned n) {
    return n < 2 ? 0 : n * (n - 1) / 2;
}
