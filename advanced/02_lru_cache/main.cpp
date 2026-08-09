#include <iostream>
#include <unordered_map>
#include <cassert>
using namespace std;

class LRUCache {
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> map;
    Node* head; // most recently used sits right after head
    Node* tail; // least recently used sits right before tail

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertAtFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
    }

    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        Node* node = map[key];
        removeNode(node);
        insertAtFront(node);
        return node->value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            Node* node = map[key];
            node->value = value;
            removeNode(node);
            insertAtFront(node);
            return;
        }

        if ((int)map.size() == capacity) {
            Node* lru = tail->prev;
            removeNode(lru);
            map.erase(lru->key);
            delete lru;
        }

        Node* node = new Node(key, value);
        map[key] = node;
        insertAtFront(node);
    }

    void printState() {
        cout << "[";
        Node* curr = head->next;
        while (curr != tail) {
            cout << "(" << curr->key << ":" << curr->value << ")";
            if (curr->next != tail) cout << " ";
            curr = curr->next;
        }
        cout << "]  (front = most recently used)" << endl;
    }
};

int main() {
    LRUCache cache(3);

    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    cout << "After inserting 1,2,3 (capacity 3): ";
    cache.printState();

    cout << "get(1) = " << cache.get(1) << endl;
    assert(cache.get(1) == 100);
    cout << "State after accessing 1 (now most recently used): ";
    cache.printState();

    cache.put(4, 400); // should evict key 2, the least recently used
    cout << "\nAfter put(4,400), key 2 should be evicted: ";
    cache.printState();
    assert(cache.get(2) == -1);
    assert(cache.get(4) == 400);

    cache.put(3, 333); // update existing key
    cout << "\nAfter updating key 3 to 333: ";
    cache.printState();
    assert(cache.get(3) == 333);

    cout << "\nget(999) (missing key) = " << cache.get(999) << endl;
    assert(cache.get(999) == -1);

    cout << "\nAll checks passed." << endl;
    return 0;
}
