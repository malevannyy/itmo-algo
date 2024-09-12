#include <iostream>

#define E int

using namespace std;

class Deque;

class SimpleDeque;

class Node {
public:
    Node(E e, Node *prev, Node *next) {
        this->e = e;
        this->prev = prev;
        this->next = next;
    }

    ~Node() = default;

    // todo private
    E e;
    Node *next;
    Node *prev;
};


class Deque {
public:
    virtual ~Deque() = default;

    virtual void push(E e) = 0;

    virtual E pop() = 0;
};

class SimpleDeque : public Deque {
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    SimpleDeque() = default;

    void push(E e) override {
        const auto node = new Node(e, nullptr, head);
        if (head != nullptr) {
            head = node;
        }
        if (tail == nullptr) {
            tail = node;
        }
        head = node;
    };

    E pop() override {
        if (head == nullptr) {
            throw new exception;
        }
        const auto e = head->e;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        return e;
    }

};

int main() {
    int n;
    cin >> n;
    const auto stack = new SimpleDeque();
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        switch (op) {
            case '+' :
                int message;
                cin >> message;
                stack->push(message);
                break;
            case '-' :
                const auto x = stack->pop();
                cout << x << endl;
                break;
        }
    }

    delete stack;
    return 0;
}
