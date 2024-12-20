#include <iostream>

using namespace std;
static const char a = 'a';
static const char z = 'z';

class Processor {
    static const unsigned alphabet_size = z - a + 1;

    struct Vertex {
        char c;
        bool fin;
        Vertex *parent = nullptr;
        Vertex *children[alphabet_size] = {nullptr};

        Vertex() {
            c = 0;
            fin = false;
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
    Vertex **index = nullptr;

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

    void rebuild(Vertex *vertex, unsigned &current) {
        if (vertex == nullptr) return;

        if (vertex->fin) {
            index[current++] = vertex;
        }

        for (auto child: vertex->children) {
            rebuild(child, current);
        }
    }

    void rebuild_index() {
        unsigned current = 0;
        index = new Vertex *[word_count];
        rebuild(root, current);
    }

    // ugly olympic stuff
    void print_word(Vertex *vertex) {
        char buf[max_length + 1];
        buf[max_length] = 0;
        char *pointer;;
        for (pointer = &buf[max_length - 1]; vertex != root; pointer--) {
            *pointer = vertex->c;
            vertex = vertex->parent;
        }

        cout << ++pointer << '\n';
    }

public:
    void accept(const string &s) {
        auto parent = root;
        for (unsigned i = 0, l = s.length() - 1; i <= l; i++) {
            parent = accept(parent, s[i], i == l);
        }
        count_max_length(s);
        word_count++;
        if(index != nullptr) {
            delete index;
            index = nullptr;
        }
    }

    void get(int i) {
        if (index == nullptr) {
            rebuild_index();
        }

        if (i < word_count) {
            auto ende = index[i];
            if (ende != nullptr) {
                print_word(ende);
            }
        }
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
            int i = atoi(input.c_str()) - 1;
            processor->get(i);
        }
    }
    delete processor;
}
