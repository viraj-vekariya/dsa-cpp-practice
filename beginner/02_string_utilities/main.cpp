#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cassert>
using namespace std;

bool isPalindrome(const string& s) {
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) {
        if (tolower(s[lo]) != tolower(s[hi])) return false;
        lo++;
        hi--;
    }
    return true;
}

bool isAnagram(string a, string b) {
    if (a.size() != b.size()) return false;
    int freq[256] = {0};
    for (char c : a) freq[(unsigned char)tolower(c)]++;
    for (char c : b) freq[(unsigned char)tolower(c)]--;
    for (int f : freq) {
        if (f != 0) return false;
    }
    return true;
}

string reverseWords(const string& s) {
    vector<string> words;
    string curr;
    for (char c : s) {
        if (c == ' ') {
            if (!curr.empty()) {
                words.push_back(curr);
                curr.clear();
            }
        } else {
            curr += c;
        }
    }
    if (!curr.empty()) words.push_back(curr);

    string result;
    for (int i = (int)words.size() - 1; i >= 0; i--) {
        result += words[i];
        if (i != 0) result += " ";
    }
    return result;
}

void countVowelsConsonants(const string& s, int& vowels, int& consonants) {
    vowels = 0;
    consonants = 0;
    string vowelSet = "aeiou";
    for (char c : s) {
        char lc = tolower(c);
        if (!isalpha(lc)) continue;
        if (vowelSet.find(lc) != string::npos) vowels++;
        else consonants++;
    }
}

int main() {
    string p1 = "racecar";
    string p2 = "hello";
    cout << "\"" << p1 << "\" is palindrome: " << (isPalindrome(p1) ? "yes" : "no") << endl;
    cout << "\"" << p2 << "\" is palindrome: " << (isPalindrome(p2) ? "yes" : "no") << endl;
    assert(isPalindrome(p1) == true);
    assert(isPalindrome(p2) == false);

    string a1 = "listen", a2 = "silent";
    cout << "\n\"" << a1 << "\" and \"" << a2 << "\" are anagrams: "
         << (isAnagram(a1, a2) ? "yes" : "no") << endl;
    string a3 = "hello", a4 = "world";
    cout << "\"" << a3 << "\" and \"" << a4 << "\" are anagrams: "
         << (isAnagram(a3, a4) ? "yes" : "no") << endl;
    assert(isAnagram(a1, a2) == true);
    assert(isAnagram(a3, a4) == false);

    string sentence = "the quick brown fox";
    cout << "\nOriginal: \"" << sentence << "\"" << endl;
    cout << "Reversed words: \"" << reverseWords(sentence) << "\"" << endl;
    assert(reverseWords(sentence) == "fox brown quick the");

    string text = "Hello World";
    int vowels, consonants;
    countVowelsConsonants(text, vowels, consonants);
    cout << "\n\"" << text << "\" has " << vowels << " vowels and "
         << consonants << " consonants" << endl;
    assert(vowels == 3 && consonants == 7);

    cout << "\nAll checks passed." << endl;
    return 0;
}
