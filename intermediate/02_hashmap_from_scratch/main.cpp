#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class HashMap {
    struct Entry {
        string key;
        int value;
        Entry* next;
        Entry(string k, int v) : key(k), value(v), next(nullptr) {}
    };

    vector<Entry*> buckets;
    int numBuckets;
    int size_;

    int hashKey(const string& key) {
        // simple polynomial rolling hash
        unsigned long h = 0;
        for (char c : key) h = h * 31 + (unsigned char)c;
        return (int)(h % numBuckets);
    }

public:
    HashMap(int bucketCount = 16) : numBuckets(bucketCount), size_(0) {
        buckets.assign(numBuckets, nullptr);
    }

    ~HashMap() {
        for (Entry* head : buckets) {
            while (head) {
                Entry* nxt = head->next;
                delete head;
                head = nxt;
            }
        }
    }

    void insert(const string& key, int value) {
        int idx = hashKey(key);
        Entry* curr = buckets[idx];
        while (curr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }
        Entry* node = new Entry(key, value);
        node->next = buckets[idx];
        buckets[idx] = node;
        size_++;
    }

    bool get(const string& key, int& valueOut) {
        int idx = hashKey(key);
        Entry* curr = buckets[idx];
        while (curr) {
            if (curr->key == key) {
                valueOut = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool remove(const string& key) {
        int idx = hashKey(key);
        Entry* curr = buckets[idx];
        Entry* prev = nullptr;
        while (curr) {
            if (curr->key == key) {
                if (prev) prev->next = curr->next;
                else buckets[idx] = curr->next;
                delete curr;
                size_--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    int size() { return size_; }

    double loadFactor() { return (double)size_ / numBuckets; }

    void printLoadFactor() {
        cout << "Load factor: " << size_ << "/" << numBuckets
             << " = " << loadFactor() << endl;
    }
};

int main() {
    HashMap map(8);

    map.insert("apple", 10);
    map.insert("banana", 20);
    map.insert("cherry", 30);
    map.insert("date", 40);
    map.insert("elderberry", 50);

    int val;
    cout << "get(apple): " << (map.get("apple", val) ? to_string(val) : "not found") << endl;
    assert(map.get("apple", val) && val == 10);

    cout << "get(banana): " << (map.get("banana", val) ? to_string(val) : "not found") << endl;
    assert(map.get("banana", val) && val == 20);

    cout << "get(missing): " << (map.get("missing", val) ? to_string(val) : "not found") << endl;
    assert(!map.get("missing", val));

    map.insert("apple", 99);
    map.get("apple", val);
    cout << "\nAfter update, get(apple): " << val << endl;
    assert(val == 99);

    bool removed = map.remove("cherry");
    cout << "\nremove(cherry): " << (removed ? "success" : "failed") << endl;
    assert(removed);
    assert(!map.get("cherry", val));

    cout << "\nCurrent size: " << map.size() << endl;
    map.printLoadFactor();
    assert(map.size() == 4);

    cout << "\nAll checks passed." << endl;
    return 0;
}
