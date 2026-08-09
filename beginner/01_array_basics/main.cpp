#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

void reverseInPlace(vector<int>& arr) {
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        swap(arr[lo], arr[hi]);
        lo++;
        hi--;
    }
}

void reverseRange(vector<int>& arr, int lo, int hi) {
    while (lo < hi) {
        swap(arr[lo], arr[hi]);
        lo++;
        hi--;
    }
}

// rotate left by k using the reverse trick: reverse first k, reverse the
// rest, then reverse the whole thing
void rotateLeft(vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;
    reverseRange(arr, 0, k - 1);
    reverseRange(arr, k, n - 1);
    reverseRange(arr, 0, n - 1);
}

void findMaxMinSecondMax(const vector<int>& arr, int& mx, int& mn, int& secondMx) {
    mx = INT_MIN;
    mn = INT_MAX;
    secondMx = INT_MIN;
    for (int x : arr) {
        if (x > mx) {
            secondMx = mx;
            mx = x;
        } else if (x > secondMx && x != mx) {
            secondMx = x;
        }
        if (x < mn) mn = x;
    }
}

// O(n^2) brute force on purpose, this is the beginner version
vector<int> twoSumBrute(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        for (int j = i + 1; j < (int)arr.size(); j++) {
            if (arr[i] + arr[j] == target) return {i, j};
        }
    }
    return {-1, -1};
}

void printArr(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < (int)arr.size(); i++) {
        cout << arr[i];
        if (i != (int)arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    cout << "Original array: ";
    printArr(a);

    vector<int> revd = a;
    reverseInPlace(revd);
    cout << "Reversed: ";
    printArr(revd);
    assert(revd[0] == 7 && revd.back() == 1);

    vector<int> rotated = a;
    rotateLeft(rotated, 3);
    cout << "Rotated left by 3: ";
    printArr(rotated);
    assert(rotated[0] == 4);

    vector<int> b = {5, 1, 9, 3, 9, 7, 2};
    int mx, mn, secondMx;
    findMaxMinSecondMax(b, mx, mn, secondMx);
    cout << "\nArray for min/max: ";
    printArr(b);
    cout << "Max: " << mx << ", Min: " << mn << ", Second max: " << secondMx << endl;
    assert(mx == 9 && mn == 1 && secondMx == 7);

    vector<int> c = {2, 7, 11, 15, 3};
    int target = 9;
    vector<int> idx = twoSumBrute(c, target);
    cout << "\nTwo sum target " << target << " in ";
    printArr(c);
    if (idx[0] != -1)
        cout << "Found at indices " << idx[0] << " and " << idx[1]
             << " (" << c[idx[0]] << " + " << c[idx[1]] << " = " << target << ")" << endl;
    else
        cout << "No pair found" << endl;
    assert(idx[0] == 0 && idx[1] == 1);

    cout << "\nAll checks passed." << endl;
    return 0;
}
