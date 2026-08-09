#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <cassert>
using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void merge(vector<int>& arr, int lo, int mid, int hi) {
    vector<int> left(arr.begin() + lo, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + hi + 1);

    int i = 0, j = 0, k = lo;
    while (i < (int)left.size() && j < (int)right.size()) {
        arr[k++] = left[i] <= right[j] ? left[i++] : right[j++];
    }
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSortHelper(vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSortHelper(arr, lo, mid);
    mergeSortHelper(arr, mid + 1, hi);
    merge(arr, lo, mid, hi);
}

void mergeSort(vector<int> arr) {
    mergeSortHelper(arr, 0, (int)arr.size() - 1);
}

int partition(vector<int>& arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int p = partition(arr, lo, hi);
    quickSortHelper(arr, lo, p - 1);
    quickSortHelper(arr, p + 1, hi);
}

void quickSort(vector<int> arr) {
    quickSortHelper(arr, 0, (int)arr.size() - 1);
}

// separate "checked" versions that return the sorted array, used for the
// small correctness demo before we move on to timing
vector<int> bubbleSortChecked(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
    return arr;
}

vector<int> mergeSortChecked(vector<int> arr) {
    mergeSortHelper(arr, 0, (int)arr.size() - 1);
    return arr;
}

vector<int> quickSortChecked(vector<int> arr) {
    quickSortHelper(arr, 0, (int)arr.size() - 1);
    return arr;
}

vector<int> randomArray(int size, int seed) {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(1, 100000);
    vector<int> arr(size);
    for (int& x : arr) x = dist(rng);
    return arr;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

int main() {
    cout << "Correctness check on a small array:" << endl;
    vector<int> sample = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    cout << "Unsorted: [";
    for (size_t i = 0; i < sample.size(); i++) cout << sample[i] << (i + 1 < sample.size() ? ", " : "");
    cout << "]" << endl;

    vector<int> b = bubbleSortChecked(sample);
    vector<int> m = mergeSortChecked(sample);
    vector<int> q = quickSortChecked(sample);
    cout << "Bubble sorted: [";
    for (size_t i = 0; i < b.size(); i++) cout << b[i] << (i + 1 < b.size() ? ", " : "");
    cout << "]" << endl;

    assert(isSorted(b));
    assert(isSorted(m));
    assert(isSorted(q));
    assert(b == m && m == q);

    cout << "\nTiming comparison on a random array (n = 3000), each run 3 times:" << endl;
    int n = 3000;
    vector<int> base = randomArray(n, 42);

    auto timeIt = [&](void (*sortFn)(vector<int>)) {
        double total = 0;
        for (int trial = 0; trial < 3; trial++) {
            auto startT = high_resolution_clock::now();
            sortFn(base);
            auto endT = high_resolution_clock::now();
            total += duration_cast<duration<double, milli>>(endT - startT).count();
        }
        return total / 3.0;
    };

    double bubbleMs = timeIt(bubbleSort);
    double mergeMs = timeIt(mergeSort);
    double quickMs = timeIt(quickSort);

    cout << left << setw(15) << "Algorithm" << setw(15) << "Avg time (ms)" << endl;
    cout << setw(15) << "Bubble sort" << setw(15) << bubbleMs << endl;
    cout << setw(15) << "Merge sort" << setw(15) << mergeMs << endl;
    cout << setw(15) << "Quick sort" << setw(15) << quickMs << endl;

    cout << "\nAll checks passed." << endl;
    return 0;
}
