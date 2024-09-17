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
            throw;
        }
        const auto e = head->e;
        const auto ex = head;
        head = head->next;
        delete ex;
        return e;
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    auto stack = Stack();
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        if (op == '+') {
            int message;
            cin >> message;
            stack.push(message);
        } else {
            printf("%d\n", stack.pop());
        }
    }

    return 0;
}