#include <iostream>
#include <string>
#include <cassert>
using namespace std;

const int CAP = 100;

class ArrayStack {
    int data[CAP];
    int top_;
public:
    ArrayStack() : top_(-1) {}

    bool isEmpty() { return top_ == -1; }
    bool isFull() { return top_ == CAP - 1; }

    void push(int val) {
        if (isFull()) {
            cout << "Stack overflow" << endl;
            return;
        }
        data[++top_] = val;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow" << endl;
            return -1;
        }
        return data[top_--];
    }

    int peek() {
        if (isEmpty()) return -1;
        return data[top_];
    }
};

class ArrayQueue {
    int data[CAP];
    int front_, rear_, count_;
public:
    ArrayQueue() : front_(0), rear_(-1), count_(0) {}

    bool isEmpty() { return count_ == 0; }
    bool isFull() { return count_ == CAP; }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue overflow" << endl;
            return;
        }
        rear_ = (rear_ + 1) % CAP;
        data[rear_] = val;
        count_++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow" << endl;
            return -1;
        }
        int val = data[front_];
        front_ = (front_ + 1) % CAP;
        count_--;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return data[front_];
    }
};

bool isBalanced(const string& expr) {
    ArrayStack stack;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            int opener = stack.pop();
            if (opener == -1) return false;
            if (c == ')' && opener != '(') return false;
            if (c == ']' && opener != '[') return false;
            if (c == '}' && opener != '{') return false;
        }
    }
    return stack.isEmpty();
}

int main() {
    ArrayStack s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "Stack peek: " << s.peek() << endl;
    cout << "Popped: " << s.pop() << endl;
    cout << "Popped: " << s.pop() << endl;
    cout << "Stack peek after pops: " << s.peek() << endl;
    assert(s.peek() == 10);

    ArrayQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << "\nQueue peek: " << q.peek() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Queue peek after dequeues: " << q.peek() << endl;
    assert(q.peek() == 3);

    cout << "\nBalanced parentheses check:" << endl;
    string tests[] = {"({[]})", "([)]", "((()))", "(()", "{[()()]}"};
    for (const string& t : tests) {
        cout << "\"" << t << "\" -> " << (isBalanced(t) ? "Balanced" : "Not balanced") << endl;
    }
    assert(isBalanced("({[]})") == true);
    assert(isBalanced("([)]") == false);
    assert(isBalanced("(()") == false);

    cout << "\nAll checks passed." << endl;
    return 0;
}
