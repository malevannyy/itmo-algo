/**
 * Кураторы Бибы и Бобы идя с лекции по хешам курили что-то запрещенное и
 * допустили две логические ошибки в условии задачи и как следствие тестах
 *
 * 1) между двумя стульями НЕТ стульев вообще,
 *    однако кураторам привиделся еще один ВНЕЗАПНО,
 *
 * 2) в формуле не хватает модуля, она не учитыват
 *    тот факт что стулья могут стоять убывающим порядком
 *
 * Всё это прискорбно.
 *
 * ---
 * Commander Lambda
 */

#include <cstdio>

using namespace std;

const auto magic_number = 17u; // 3
const auto magic_mask = (1u << magic_number) - 1;
const auto number = 1u << magic_number; // 100000 // 6

unsigned a[number]{};

unsigned foo(unsigned);

int main() {
    unsigned n;
    unsigned shift = 1;
    unsigned count = 0;
    scanf("%d", &n);
    for (; shift < n; shift <<= 1);

    for (unsigned i = n; i > 0; i--) {
        unsigned hi;
        scanf("%d", &hi);
        auto x = hi + i - 1;
        auto imagine = x / number;
        auto real = x % number;
        auto old_imagine = a[real] >> magic_number;
        if (imagine == old_imagine) {
            a[real]++;
        } else {
            auto accum = a[real] & magic_mask;
            count += foo(accum);
            a[real] = (imagine << magic_number) + 1;
        }
    }

    for (unsigned tuple: a) {
        auto accum = tuple & magic_mask;
        count += foo(accum);
    }

    printf("%u", count);
}

unsigned foo(unsigned n) {
    return n < 2 ? 0 : n * (n - 1) / 2;
}
