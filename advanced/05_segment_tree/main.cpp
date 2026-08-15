#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class SegmentTree {
    int n;
    vector<long long> tree;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) update(2 * node + 1, start, mid, idx, value);
        else update(2 * node + 2, mid + 1, end, idx, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0; // no overlap
        if (l <= start && end <= r) return tree[node]; // total overlap
        int mid = start + (end - start) / 2;
        return query(2 * node + 1, start, mid, l, r) +
               query(2 * node + 2, mid + 1, end, l, r);
    }

public:
    explicit SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }

    long long rangeSum(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Array: [1, 3, 5, 7, 9, 11]" << endl;

    cout << "sum(0,5) = " << st.rangeSum(0, 5) << endl;
    assert(st.rangeSum(0, 5) == 36);

    cout << "sum(1,3) = " << st.rangeSum(1, 3) << endl;
    assert(st.rangeSum(1, 3) == 15); // 3+5+7

    cout << "sum(2,2) = " << st.rangeSum(2, 2) << endl;
    assert(st.rangeSum(2, 2) == 5);

    st.update(1, 10); // arr becomes [1, 10, 5, 7, 9, 11]
    cout << "\nAfter update(idx=1, value=10):" << endl;
    cout << "sum(0,5) = " << st.rangeSum(0, 5) << endl;
    assert(st.rangeSum(0, 5) == 43);

    cout << "sum(0,1) = " << st.rangeSum(0, 1) << endl;
    assert(st.rangeSum(0, 1) == 11); // 1+10

    st.update(5, 0); // arr becomes [1, 10, 5, 7, 9, 0]
    cout << "\nAfter update(idx=5, value=0):" << endl;
    cout << "sum(4,5) = " << st.rangeSum(4, 5) << endl;
    assert(st.rangeSum(4, 5) == 9);

    cout << "\nAll checks passed." << endl;
    return 0;
}
