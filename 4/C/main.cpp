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

void bar(int a, int l, int sl) {
    for (int i = 0; i <= l; i++) {
        cout << ' ';
    }
    for (int i = 0; i < sl - l - 1; i++) {
        char c = '.';
        if (i >= a && i < a + l) {
            c = '-';
        }

        cout << c;
    }
    cout << endl;
}

void zoo(int n) {
    for (int i = 0; i < n; i++) {
        cout << (i % 10);
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

    for (int j = 0; j < m; j++) {
        int a, b, l;
        cin >> a >> b >> l;

        auto prefix = origin.substr(a - 1, a - 1 + l);
        auto s = prefix + "|" + origin;
        auto sl = (int) s.length();
        int pf[sl];
        prefix_fun(pf, s.c_str(), sl);

        zoo(sl);
        cout << s << endl;
        foo(pf, sl);
        bar(a - 1, l, sl);
        bar(b - 1, l, sl);

        if (pf[b - 1 + l + l] == l && pf[a - 1 + l + l] == l) {
            count++;
        }

    }

    cout << count;
}
