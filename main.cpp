#include <iostream>

#define E int

using namespace std;

struct Node {
    Node(E e, Node *next) {
        this->e = e;
        this->next = next;
    }

    ~Node() = default;

    E e;
    Node *next;
};

class Stack {
private:
    Node *head = nullptr;

public:
    Stack() = default;

    void push(E e) {
        head = new Node(e, head);
    };

    E pop() {
        if (head == nullptr) {
            throw new exception;
        }
        const auto e = head->e;
        const auto ex = head;
        head = head->next;
        delete ex;
        return e;
    }

};

int main() {
    int n;
    cin >> n;
    const auto stack = new Stack();
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
                cout << stack->pop() << endl;
                break;
        }
    }

    delete stack;
    return 0;
}
