#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->val) node->left = insert(node->left, val);
        else if (val > node->val) node->right = insert(node->right, val);
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->val) {
            node->left = remove(node->left, val);
        } else if (val > node->val) {
            node->right = remove(node->right, val);
        } else {
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            }
            // two children: swap in the inorder successor's value, then
            // delete that successor node from the right subtree
            Node* successor = findMin(node->right);
            node->val = successor->val;
            node->right = remove(node->right, successor->val);
        }
        return node;
    }

    void inorder(Node* node, vector<int>& out) {
        if (!node) return;
        inorder(node->left, out);
        out.push_back(node->val);
        inorder(node->right, out);
    }

    void preorder(Node* node, vector<int>& out) {
        if (!node) return;
        out.push_back(node->val);
        preorder(node->left, out);
        preorder(node->right, out);
    }

    void postorder(Node* node, vector<int>& out) {
        if (!node) return;
        postorder(node->left, out);
        postorder(node->right, out);
        out.push_back(node->val);
    }

    int height(Node* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val) { root = insert(root, val); }
    void remove(int val) { root = remove(root, val); }

    bool search(int val) {
        Node* curr = root;
        while (curr) {
            if (val == curr->val) return true;
            curr = val < curr->val ? curr->left : curr->right;
        }
        return false;
    }

    vector<int> inorder() {
        vector<int> out;
        inorder(root, out);
        return out;
    }

    vector<int> preorder() {
        vector<int> out;
        preorder(root, out);
        return out;
    }

    vector<int> postorder() {
        vector<int> out;
        postorder(root, out);
        return out;
    }

    int height() { return height(root); }
};

void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    BST tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10};
    for (int v : values) tree.insert(v);

    cout << "Inserted: ";
    printVec(vector<int>(begin(values), end(values)));

    cout << "\nInorder (should be sorted): ";
    printVec(tree.inorder());
    vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80};
    assert(tree.inorder() == expected);

    cout << "Preorder: ";
    printVec(tree.preorder());

    cout << "Postorder: ";
    printVec(tree.postorder());

    cout << "\nSearch 40: " << (tree.search(40) ? "found" : "not found") << endl;
    cout << "Search 999: " << (tree.search(999) ? "found" : "not found") << endl;
    assert(tree.search(40) == true);
    assert(tree.search(999) == false);

    cout << "\nHeight of tree: " << tree.height() << endl;
    assert(tree.height() == 3);

    tree.remove(30);
    cout << "\nAfter deleting 30, inorder: ";
    printVec(tree.inorder());
    assert(tree.search(30) == false);

    tree.remove(50);
    cout << "After deleting root (50), inorder: ";
    printVec(tree.inorder());
    assert(tree.search(50) == false);

    cout << "\nAll checks passed." << endl;
    return 0;
}
