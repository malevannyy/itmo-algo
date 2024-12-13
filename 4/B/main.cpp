#include <iostream>

using namespace std;

void prefix_fun(int *p, const char *s, int n) {
    for (int i = 0; i < n; i++) {
        p[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
}

void foo(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    // cout << endl;
}

int main() {
    string origin;
    getline(cin, origin);

    auto n = (int) origin.length();
    int pf[n];
    prefix_fun(pf, origin.c_str(), n);

    foo(pf, n);

}
