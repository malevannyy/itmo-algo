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
        cout << a[i];
    }
    cout << endl;
}

int main() {
    string t;
    string s;
    getline(cin, t);
    getline(cin, s);

    auto origin = s + "|" + t;
    auto n = (int) origin.length();
    int pf[n];
    prefix_fun(pf, origin.c_str(), n);
    int sl = (int) s.length();

    int result[200000];
    auto result_index = 0;

    for (int i = n - 1; i >= 2 * sl; i--) {
        if (pf[i] == sl) {
            result[result_index++] = i - sl - sl;
        }
    }

    cout << result_index << endl;
    for (int i = result_index-1; i >= 0; i--) {
        cout << result[i] << ' ';
    }
}
