#include <iostream>

using namespace std;


int main() {
    // длина текста песни ≤1e6
    int n;
    // количество вопросов фанатов ≤1e5
    int m;
    cin >> n >> m;
    getchar();
    string origin;
    getline(cin, origin);
    int count = 0;

    for (int k = 0; k < m; k++) {
        int a, b, l;
        cin >> a >> b >> l;

        for (int i = a - 1, j = b - 1; i < a - 1 + l; i++, j++) {
            if (origin[i] != origin[j]) {
                goto outer_label;
            }
        }
        count++;
        outer_label:;

    }

    cout << count;
}
