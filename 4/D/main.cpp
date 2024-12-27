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
        Vertex **children = nullptr;

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

    unsigned word_count;
    unsigned max_length = 0;
    Vertex *root = new Vertex();
    Vertex **index;
    bool built = false;

    Vertex *accept(Vertex *parent, char c, bool fin) { // NOLINT(*-convert-member-functions-to-static)
        unsigned i = c - a;
        if (parent->children == nullptr) {
            parent->children = new Vertex *[alphabet_size]{};
        }
        auto child = parent->children[i];
        if (child != nullptr) {
            if(fin) {
                child->fin = fin;
            }
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

        if (vertex->children != nullptr) {
            for (int i = 0; i < alphabet_size; i++) {
                auto child = vertex->children[i];
                if (child != nullptr) {
                    rebuild(child, current);
                }
            }
        }
    }

    void rebuild_index() {
        // clear? for what? contents would be overwritten
        unsigned current = 0;
        rebuild(root, current);
        built = true;
    }

    // ugly olympic stuff
    void print_word(Vertex *vertex) {
        char buf[max_length + 1];
        buf[max_length] = 0;
        char *p;
        for (p = &buf[max_length - 1]; vertex != root; p--) {
            *p = vertex->c;
            vertex = vertex->parent;
        }

        //printf(++p);
        puts(++p);
    }

public:
    void accept(const string &s) {
        auto parent = root;
        auto length = s.length();
        for (unsigned i = 0, l = length - 1; i <= l; i++) {
            parent = accept(parent, s[i], i == l);
        }

        if (length > max_length) {
            max_length = length;
        }

        word_count++;

        // fixme
        built = false;
    }

    void get(int i) {
        if (!built) {
            rebuild_index();
        }

        if (i < word_count) {
            auto ende = index[i];
            if (ende != nullptr) {
                print_word(ende);
            }
        }
    }

    explicit Processor(const unsigned n) : word_count(n) {
        index = new Vertex *[word_count];
    }
};

int main() {
    unsigned n;
    cin >> n;
    getchar();
    auto processor = new Processor(n);
    string input;
    for (int k = 0; k < n; k++) {
        getline(cin, input);
        if (input[0] >= a) {
            processor->accept(input);
            input.clear();
        } else {
            int i = atoi(input.c_str()) - 1;
            processor->get(i);
        }
    }
    // ugly olympic stuff
    // delete processor;
}
