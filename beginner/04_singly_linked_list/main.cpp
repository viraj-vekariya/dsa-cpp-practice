#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* curr = head;
        while (curr) {
            Node* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
    }

    void insertHead(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }

    void insertTail(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
            return;
        }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }

    bool deleteValue(int val) {
        if (!head) return false;
        if (head->val == val) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }
        Node* curr = head;
        while (curr->next && curr->next->val != val) curr = curr->next;
        if (!curr->next) return false;
        Node* toDelete = curr->next;
        curr->next = toDelete->next;
        delete toDelete;
        return true;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        head = prev;
    }

    // Floyd's cycle detection: fast pointer moves 2 steps, slow moves 1.
    // If they ever meet, there's a cycle.
    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    // exposed only so main() can build a cycle for the demo
    Node* getHead() { return head; }
    Node* getTail() {
        Node* curr = head;
        while (curr && curr->next) curr = curr->next;
        return curr;
    }

    void print() {
        Node* curr = head;
        cout << "[";
        while (curr) {
            cout << curr->val;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "]" << endl;
    }
};

int main() {
    LinkedList list;
    list.insertTail(1);
    list.insertTail(2);
    list.insertTail(3);
    list.insertHead(0);
    cout << "List after inserts: ";
    list.print();

    list.deleteValue(2);
    cout << "After deleting 2: ";
    list.print();
    assert(list.deleteValue(999) == false);

    list.reverse();
    cout << "After reverse: ";
    list.print();

    LinkedList cyclic;
    cyclic.insertTail(1);
    cyclic.insertTail(2);
    cyclic.insertTail(3);
    cyclic.insertTail(4);
    cout << "\nCyclic list (no cycle yet) has cycle: " << (cyclic.hasCycle() ? "yes" : "no") << endl;
    assert(cyclic.hasCycle() == false);

    // manually wire the tail back to the head to create a cycle
    Node* tail = cyclic.getTail();
    tail->next = cyclic.getHead();
    cout << "After linking tail back to head, has cycle: " << (cyclic.hasCycle() ? "yes" : "no") << endl;
    assert(cyclic.hasCycle() == true);

    // unlink before the destructor runs, otherwise it walks the cycle forever
    tail->next = nullptr;

    cout << "\nAll checks passed." << endl;
    return 0;
}
