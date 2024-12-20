#include <iostream>

using namespace std;
static const char a = 'a';

class Processor {
    static const unsigned alphabet_size = 32;

    class Vertex {
        char c;
        bool fin;
        int index = -1;
        Vertex *parent = nullptr;
        Vertex *children[alphabet_size] = {nullptr};
    public:
        Vertex() {
            c = 0;
            fin = false;
            index = -1;
            parent = nullptr;
        }

        Vertex(char c,
               bool fin,
               int index,
               Vertex *parent = nullptr
        ) : c(c),
            fin(fin),
            index(index),
            parent(parent) {}
    };

    unsigned max_length = 0;
    Vertex *root = new Vertex();


public:
    void accept(const string &s) {
        auto length = s.length();
        if (length > max_length) {
            max_length = length;
        }

    }

    void get(int i) {
        char buf[max_length];





        // ugly olympic stuff
        cout << buf;
    }
};

int main() {
    // query count ≤1e5
    int n;
    cin >> n;
    getchar();
    auto processor = new Processor();
    for (int k = 0; k < n; k++) {
        string input;
        getline(cin, input);
        if (input[0] >= a) {
            processor->accept(input);
            input.clear();
        } else {
            int i = atoi(input.c_str());
            processor->get(i);
        }
    }
    delete processor;
}
