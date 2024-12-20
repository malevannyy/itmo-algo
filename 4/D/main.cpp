#include <iostream>

using namespace std;
static const char a = 'a';
static const char z = 'z';

class Processor {
    static const unsigned alphabet_size = z - a + 1;

    struct Vertex {
        char c;
        bool fin;
        int index = -1;
        Vertex *parent = nullptr;
        Vertex *children[alphabet_size] = {nullptr};

        Vertex() {
            c = 0;
            fin = false;
            index = -1;
            parent = nullptr;
        }

        Vertex(char c,
               bool fin,
               Vertex *parent = nullptr
        ) : c(c),
            fin(fin),
            parent(parent) {}
    };

    unsigned word_count = 0;
    unsigned max_length = 0;
    Vertex *root = new Vertex();
    // todo index

    void count_max_length(const string &s) {
        auto length = s.length();
        if (length > max_length) {
            max_length = length;
        }
    }

    static Vertex *accept(Vertex *parent, char c, bool fin) {
        unsigned i = c - a;
        auto child = parent->children[i];
        if (child != nullptr) {
            child->fin |= fin;
        } else {
            child = new Vertex(c, fin, parent);
            parent->children[i] = child;
        }
        return child;
    }

public:
    void accept(const string &s) {
        auto parent = root;
        for (unsigned i = 0, l = s.length() - 1; i <= l; i++) {
            parent = accept(parent, s[i], i == l);
        }
        count_max_length(s);
        word_count++;
        // todo clear index
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
