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
    // длина текста песни ≤1e6
    int n;
    // количество вопросов фанатов ≤1e5
    int m;
    string origin;
    cin >> n >> m;
    getchar();
    getline(cin, origin);
    int count = 0;

    int pf[n];
    prefix_fun(pf, origin.c_str(), n);

    for (int j = 0; j < m; j++) {
        int a, b, l;
        cin >> a >> b >> l;

        if (pf[a - 1 + l] == l && pf[b - 1 + l] == l) {
            count++;
        }

    }

    cout << count;
}
