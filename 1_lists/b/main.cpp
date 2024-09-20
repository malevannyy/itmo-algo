#include <iostream>

#define E int

using namespace std;

class Queue {
public:
    virtual void add(E e) = 0;

    virtual E remove() = 0;

    virtual E element() = 0;

    virtual ~Queue() = default;
};

class LinkedQueue : Queue {
private:
    struct Node {
        E e;
        Node *next;

        explicit Node(E e, Node *next = nullptr) {
            this->e = e;
            this->next = next;
        }

        ~Node() = default;
    };

    Node *head = nullptr;
    Node *tail = nullptr;

public:
    LinkedQueue() = default;

    void add(E e) override {
        const auto n = new Node(e);
        if (tail != nullptr) {
            tail->next = n;
            tail = n;
        } else {
            head = tail = n;
        }
    };

    E remove() override {
        if (head == nullptr) {
            throw;
        }
        const auto h = head;
        const auto e = h->e;
        head = h->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete (h);
        return e;
    }

    E element() override {
        if (head == nullptr) {
            throw;
        }
        return head->e;
    }

};

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    auto deque = LinkedQueue();
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        if (op == '+') {
            int message;
            cin >> message;
            deque.add(message);
        } else {
            printf("%d\n", deque.remove());
        }
    }

    return 0;
}