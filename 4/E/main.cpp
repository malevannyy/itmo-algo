#include <iostream>

using namespace std;
static const char a = 'a';
static const char z = 'z';
static const char A = 'A';
static const char Z = 'Z';
static const char z0 = '0';
static const char z9 = '9';

bool fio(const string &s) {
    for (unsigned i = 0, l = s.length(); i < l; i++) {
        auto c = s[i];
        if (i == 0) {
            if (!(A <= c && c <= Z)) {
                return false;
            }
        } else {
            if (!(a <= c && c <= z)) {
                return false;
            }

        }
    }

    return true;
}

bool age(const string &s) {
    if (s.length() == 2) {
        char c1 = s[0];
        char c2 = s[1];
        if (z0 <= c1 && c1 <= z9 && z0 <= c2 && c2 <= z9) {
            return true;
        }
    }
    return false;
}

bool tel(const string &s) {
    if (s.length() < 11) {
        return false;
    }
    unsigned count = 1;
    unsigned b;

    if (s[0] == '+' && s[1] == '7') {
        b = 2;
    } else if (s[0] == '8' || s[0] == '7') {
        b = 1;
    } else {
        return false;
    }

    for (unsigned i = b, l = s.length(); i < l; i++) {
        char c = s[i];
        if (c == '(' || c == ')' || c == '-') {
            continue;
        } else if (z0 <= c && c <= z9) {
            count++;
            continue;
        } else {
            return false;
        }
    }

    return count == 11;
}

bool AZ(char c) {
    return A <= c && c <= Z;
}

bool az(char c) {
    return a <= c && c <= z;
}

bool d(char c) {
    return '0' <= c && c <= '9';
}

bool gor(const string &s) {
    if (s.length() != 5) {
        return false;
    } else if (s[0] == 'g' && s[1] == ',' && AZ(s[2]) && AZ(s[3]) && AZ(s[4])) {
        return true;
    } else {
        return false;
    }
}

bool ul(const string &s) {
    if (s.length() < 4) {
        return false;
    }

    if (s[0] != 'u' || s[1] != 'l' || s[2] != '.' || !AZ(s[3])) {
        return false;
    }

    for (unsigned i = 4, l = s.length(); i < l; i++) {
        if (!az(s[i])) {
            return false;
        }
    }
    return true;
}

void no() {
    printf("NO\n");
}

// TODO regex!!!
int main() {
    int n;
    cin >> n;
    getchar();

    string s;
    for (int k = 0; k < n; k++) {

        cin >> s;
        if (!fio(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!fio(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!fio(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!age(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!tel(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!gor(s)) {
            no();
            continue;
        }

        cin >> s;
        if (!ul(s)) {
            no();
            continue;
        }

        cout << "YES" << '\n';
    }
}
