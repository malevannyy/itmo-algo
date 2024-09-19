#include <iostream>
#include <chrono>
#include "main.cpp"

#define nl '\n'

using namespace std::chrono;
using namespace std;

duration<long long int, ratio<1, 1000>> now() {
    return duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
    );
}

void foo() {

    auto stack = LinkedDeque();

    for (int i = 0; i < 1000000; ++i) {
        stack.add(i);
    }

    for (int i = 0; i < 1000000; ++i) {
        int e = stack.remove();
        printf("%d\n", e);
        // cout << e << nl;
    }

}

int main1(int argc, char **argv) {
    std::ios::sync_with_stdio(false);

    auto start = high_resolution_clock::now();

    foo();

    auto finish = high_resolution_clock::now();
    duration<double, std::milli> elapsed = finish - start;

    cout << "Elapsed Time: " << elapsed.count() << std::endl;

    return 0;
}

