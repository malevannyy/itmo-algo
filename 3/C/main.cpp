#include <cstdio>

#pragma ide diagnostic ignored "cert-err34-foo"

const auto magic_number = 17u;
const auto odd_number = 15u;
const auto odd_mask = (1u << odd_number) - 1;
const auto number = 1u << magic_number;

unsigned a[number]{};

unsigned foo(unsigned);

int main() {
    unsigned n;
    unsigned count = 0;
    unsigned old_imagine;
    scanf("%d", &n);
    for (unsigned i = 0; i < n; i++) {
        unsigned hi;
        scanf("%d", &hi);
        auto x = hi - i + n;
        auto imagine = x / magic_number; // >> betta
        auto real = x % magic_number; // &

        old_imagine = a[real] >> odd_number;

        if (imagine == old_imagine) {
            a[real]++;
        } else {
            count = +foo(a[real] & odd_mask);
            a[real] = (imagine << odd_number) + 1;
        }
    }

    for (unsigned ic: a) {
        auto imagine = ic >> odd_number;
        if (imagine == old_imagine) {
            count += foo(ic & odd_mask);
        }
    }

    printf("%u", count);
}

unsigned foo(unsigned n) {
    return n < 2 ? 0 : n * (n - 1) / 2;
}
