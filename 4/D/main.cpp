#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "MemoryLeak"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

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
        Vertex *next = nullptr;

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

        Vertex *most_right_child_until_or_this(char right_bound = z + 1) {
            if (this->children != nullptr) {
                for (int i = right_bound - a - 1; i >= 0; --i) {
                    auto w = this->children[i];
                    if (w != nullptr) {
                        return w;
                    }
                }
            }
            return this;
        }

        Vertex *find_prev_or_null() {
            // up loop
            Vertex *rop;
            for (auto child = this, v = child->parent;
                 v != nullptr;
                 child = v, v = v->parent) {
                rop = v->most_right_child_until_or_this(child->c);
                if (rop->parent == nullptr) {
                    return nullptr;
                } else if (rop != v) {
                    break;
                } else if (rop->fin) {
                    return rop;
                }
            }

            // down loop
            auto maybe_down = rop->most_right_child_until_or_this();
            for (auto t = rop;
                 maybe_down != t;
                 t = maybe_down, maybe_down = maybe_down->most_right_child_until_or_this()) {
            }
            return maybe_down;
        }
    };

    Vertex *root = new Vertex();
    Vertex *head = nullptr;

    unsigned word_count = 0;
    unsigned max_length = 0;

    Vertex *accept(Vertex *parent, char c, bool fin) {
        unsigned i = c - a;
        if (parent->children == nullptr) {
            parent->children = new Vertex *[alphabet_size]{};
        }
        auto child = parent->children[i];
        if (child != nullptr) {
            if (fin) {
                child->fin = fin;
            }
        } else {
            child = new Vertex(c, fin, parent);
            parent->children[i] = child;
        }
        return child;
    }

    void print_word(Vertex *vertex) {
        char buf[max_length + 1];
        buf[max_length] = 0;
        char *p;
        for (p = &buf[max_length - 1]; vertex != root; p--) {
            *p = vertex->c;
            vertex = vertex->parent;
        }

        puts(++p);
    }

public:
    void accept(const string &s) {
        auto vertex = root;
        auto length = s.length();
        char c;
        for (unsigned i = 0, l = length - 1; i <= l; i++) {
            c = s[i];
            vertex = accept(vertex, c, i == l);
        }

        auto prev = vertex->find_prev_or_null();
        if (prev == nullptr) {
            vertex->next = head;
            head = vertex;
        } else {
            vertex->next = prev->next;
            prev->next = vertex;
        }

        if (length > max_length) {
            max_length = length;
        }

        word_count++;

        // debug
        // {
        //     cout << s << ": ";
        //     for (auto p = head; p != nullptr; p = p->next) {
        //         cout << p->c << "->";
        //     }
        //     cout << "null" << '\n';
        // }
    }

    void print_out(int n) {
        auto v = head;
        for (int i = 0;
             i < n && i < word_count && v != nullptr;
             i++, v = v->next);
        print_word(v);
    }
};

int main() {
    unsigned n;
    cin >> n;
    getchar();
    auto processor = new Processor();
    string input;
    for (int k = 0; k < n; k++) {
        getline(cin, input);
        if (input[0] >= a) {
            processor->accept(input);
            input.clear();
        } else {
            int i = atoi(input.c_str()) - 1; // NOLINT(*-err34-c)
            processor->print_out(i);
        }
    }
}

#pragma clang diagnostic pop
