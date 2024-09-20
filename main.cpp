#include <iostream>

#define E int

using namespace std;

class Queue {
public:
    virtual void add(E e) = 0;

    virtual E remove() = 0;

    virtual int size() = 0;

    virtual ~Queue() = default;
};

class Deque : Queue {
public:
    virtual void addLast(E e) {
        add(e);
    }

    virtual void addFirst(E e) = 0;

    virtual E removeFirst() {
        return remove();
    }

    virtual E removeLast() = 0;

    ~Deque() override = default;
};

class LinkedDeque : public Deque {
private:
    struct Node {
        E e;
        Node *next;
        Node *prev;

        explicit Node(E e, Node *next = nullptr, Node *prev = nullptr) {
            this->e = e;
            this->next = next;
            this->prev = prev;
        }

        ~Node() = default;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int count = 0;

public:
    LinkedDeque() = default;

    void add(E e) override {
        const auto n = new Node(e, nullptr, tail);
        if (tail != nullptr) {
            tail->next = n;
            tail = n;
        } else {
            head = tail = n;
        }
        ++count;
    };

    void addFirst(E e) override {
        const auto n = new Node(e, head, nullptr);
        if (head != nullptr) {
            head->prev = n;
            head = n;
        } else {
            head = tail = n;
        }
        ++count;
    }

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
        delete h;
        --count;
        return e;
    }

    E removeLast() override {
        if (tail == nullptr) {
            throw;
        }
        const auto t = tail;
        const auto e = t->e;
        tail = t->prev;
        if (tail == nullptr) {
            head = nullptr;
        }
        delete t;
        --count;
        return e;
    }

    int size() override {
        return count;
    }

    ~LinkedDeque() override = default;
};

int main() {
    std::ios::sync_with_stdio(false);

    int n, size;
    cin >> n;
    cin >> size;
    auto deque = LinkedDeque();
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (deque.size() < size) {
            deque.addFirst(t);
        } else {
            const auto a = deque.removeFirst();
            const auto b = deque.removeLast();
            const auto ta = t >= a ? t : a;
            const auto tb = t >= b ? t : b;
            if (ta < tb) {
                deque.addFirst(ta);
                deque.addFirst(tb);
            } else {
                deque.addFirst(tb);
                deque.addFirst(ta);
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        cout << deque.removeLast();
        if (i < size - 1) {
            cout << ' ';
        }
    }

    return 0;
}