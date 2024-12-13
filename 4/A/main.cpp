#include <iostream>
#include <vector>
#define T vector<int>
using namespace std;

T prefix_fun(string s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}

void foo(T a) {
    for(int i = 0; i<a.size(); i++) {
        cout << a[i];
    }
    cout << endl;
}

int main() {

    int bullshit[200000];
    auto bullshit_index = 0;

    string t;
    string s;
    getline(cin, t);
    getline(cin, s);

    auto x = prefix_fun(t);
    auto y = prefix_fun(s);
    auto z = prefix_fun(s + "|" + t);

    foo(z);

    cout << bullshit_index << endl;
    for (int index = 0; index < bullshit_index; index++) {
        cout << bullshit[index] << ' ';
    }

}
