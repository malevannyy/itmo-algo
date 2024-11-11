#include <cstdio>

long foo(int n);

#pragma ide diagnostic ignored "cert-err34-c"

int main(int argc, char **argv) {

    int n;
    scanf("%d", &n);

    auto h0 = foo(n);
    auto h1 = foo(n);

    if (h0 == h1) {
        printf("YES");
    } else {
        printf("NO");
    }
}

long foo(int n) {
    int e;
    long h = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &e);
        h += e << (e % 13);
    }
    return h;
}

