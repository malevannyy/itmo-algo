#include <iostream>

#define E int

using namespace std;

bool check(const int *coords, unsigned n, unsigned k, int x) {
    int items = 1;
    int last = coords[0];
    for (int i = 0; i < n; ++i) {
        int c = coords[i];
        if (c - last >= x) {
            items++;
            last = c;
        }
    }
    return items >= k;
}

int main() {
    std::ios::sync_with_stdio(false);

    unsigned n, k;
    // 2 <= места
    cin >> n;
    // 1 < бояре < n
    cin >> k;

    int coords[n];
    for (int i = 0; i < n; ++i) {
        cin >> coords[i];
    }

    int max = 0;
    int range = coords[n - 1] - coords[0] + 1;
    while (range - max > 1) {
        int m = (max + range) / 2;
        if (check(coords, n, k, m))
            max = m;
        else
            range = m;
    }
    cout << max;

    return 0;
}