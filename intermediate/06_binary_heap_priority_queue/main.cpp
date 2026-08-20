#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
using namespace std;

template <typename T, typename Compare = less<T>>
class MinHeap {
    vector<T> data;
    Compare cmp;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && cmp(data[i], data[parent(i)])) {
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int n = data.size();
        while (true) {
            int smallest = i;
            int l = left(i), r = right(i);
            if (l < n && cmp(data[l], data[smallest])) smallest = l;
            if (r < n && cmp(data[r], data[smallest])) smallest = r;
            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

public:
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

    void push(const T& value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    T pop() {
        assert(!data.empty());
        T top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
        return top;
    }

    const T& peek() const {
        assert(!data.empty());
        return data[0];
    }
};

int main() {
    MinHeap<int> heap;
    vector<int> input = {17, 3, 25, 1, 9, 42, 8, 14, 2};
    for (int v : input) heap.push(v);

    cout << "Pushed: ";
    for (int v : input) cout << v << " ";
    cout << endl;

    cout << "peek() = " << heap.peek() << endl;
    assert(heap.peek() == 1);

    vector<int> popped;
    while (!heap.empty()) popped.push_back(heap.pop());

    cout << "Popped in order: ";
    for (int v : popped) cout << v << " ";
    cout << endl;

    vector<int> expected = input;
    sort(expected.begin(), expected.end());
    assert(popped == expected);

    cout << "\nAll checks passed." << endl;
    return 0;
}
