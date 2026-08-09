#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>
using namespace std;

class Trie {
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        bool isWord = false;
    };

    TrieNode* root;

    TrieNode* walkToPrefix(const string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) return nullptr;
            curr = curr->children[c];
        }
        return curr;
    }

    void collectWords(TrieNode* node, string& path, vector<string>& out) {
        if (node->isWord) out.push_back(path);
        for (auto& [ch, child] : node->children) {
            path.push_back(ch);
            collectWords(child, path, out);
            path.pop_back();
        }
    }

    void destroy(TrieNode* node) {
        for (auto& [ch, child] : node->children) destroy(child);
        delete node;
    }

public:
    Trie() { root = new TrieNode(); }
    ~Trie() { destroy(root); }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = walkToPrefix(word);
        return node != nullptr && node->isWord;
    }

    bool startsWith(const string& prefix) {
        return walkToPrefix(prefix) != nullptr;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* node = walkToPrefix(prefix);
        vector<string> results;
        if (!node) return results;
        string path = prefix;
        collectWords(node, path, results);
        sort(results.begin(), results.end());
        return results;
    }
};

int main() {
    Trie trie;
    vector<string> dictionary = {
        "cat", "car", "card", "care", "careful", "dog", "dodge", "do", "done"
    };
    for (const string& w : dictionary) trie.insert(w);

    cout << "Dictionary: ";
    for (const string& w : dictionary) cout << w << " ";
    cout << endl;

    cout << "\nsearch(\"car\"): " << (trie.search("car") ? "found" : "not found") << endl;
    cout << "search(\"ca\"): " << (trie.search("ca") ? "found" : "not found") << endl;
    assert(trie.search("car") == true);
    assert(trie.search("ca") == false);

    cout << "startsWith(\"ca\"): " << (trie.startsWith("ca") ? "yes" : "no") << endl;
    cout << "startsWith(\"xyz\"): " << (trie.startsWith("xyz") ? "yes" : "no") << endl;
    assert(trie.startsWith("ca") == true);
    assert(trie.startsWith("xyz") == false);

    cout << "\nAutocomplete for \"ca\": ";
    vector<string> results = trie.autocomplete("ca");
    for (const string& w : results) cout << w << " ";
    cout << endl;
    vector<string> expected = {"car", "card", "care", "careful", "cat"};
    assert(results == expected);

    cout << "Autocomplete for \"do\": ";
    vector<string> results2 = trie.autocomplete("do");
    for (const string& w : results2) cout << w << " ";
    cout << endl;
    assert((results2 == vector<string>{"do", "dodge", "dog", "done"}));

    cout << "Autocomplete for \"zz\" (no matches): ";
    vector<string> results3 = trie.autocomplete("zz");
    cout << (results3.empty() ? "(none)" : "") << endl;
    assert(results3.empty());

    cout << "\nAll checks passed." << endl;
    return 0;
}
