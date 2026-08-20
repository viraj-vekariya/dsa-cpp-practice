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

// One element pulled off a source list, tagged with where it came from so
// we know which list to pull the next element from once this one is popped.
struct HeapItem {
    int value;
    int listIndex;
    int elemIndex;
};

struct HeapItemLess {
    bool operator()(const HeapItem& a, const HeapItem& b) const {
        return a.value < b.value;
    }
};

// Merges k already-sorted lists into one sorted list in O(N log k), where N
// is the total element count: at most k items are ever in the heap at once,
// so each of the N pushes/pops costs O(log k) instead of the O(log N) a heap
// holding every element up front would cost, and it never materializes more
// than k+1 elements at a time.
vector<int> mergeKSortedLists(const vector<vector<int>>& lists) {
    MinHeap<HeapItem, HeapItemLess> heap;
    for (int i = 0; i < (int)lists.size(); i++) {
        if (!lists[i].empty()) {
            heap.push({lists[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!heap.empty()) {
        HeapItem top = heap.pop();
        result.push_back(top.value);
        int nextIdx = top.elemIndex + 1;
        if (nextIdx < (int)lists[top.listIndex].size()) {
            heap.push({lists[top.listIndex][nextIdx], top.listIndex, nextIdx});
        }
    }
    return result;
}

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

    // Single-element heap: push then pop should round-trip cleanly.
    MinHeap<int> single;
    single.push(99);
    assert(single.peek() == 99);
    assert(single.pop() == 99);
    assert(single.empty());

    // k-way merge demo: three sorted lists, one of them empty, merged into one.
    vector<vector<int>> lists = {
        {1, 4, 9, 20},
        {},
        {2, 2, 3, 15, 30}
    };
    vector<int> merged = mergeKSortedLists(lists);

    cout << "\nk-way merge of {1,4,9,20}, {}, {2,2,3,15,30}:" << endl;
    cout << "  ";
    for (int v : merged) cout << v << " ";
    cout << endl;

    vector<int> mergedExpected = {1, 2, 2, 3, 4, 9, 15, 20, 30};
    assert(merged == mergedExpected);
    assert(merged.size() == 9);

    cout << "\nAll checks passed." << endl;
    return 0;
}
