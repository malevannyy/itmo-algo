#include <iostream>

using namespace std;

class Deque;

class SimpleDeque;

class Deque {
public:
    virtual ~Deque() = default;

    virtual void push(int e) = 0;

    virtual int pop() = 0;
};

class SimpleDeque : public Deque {
public:
    void push(int e) override {

    }

    int pop() override {
        return 0;
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
                cout << x;
                break;
        }
    }

    delete stack;
    return 0;
}
