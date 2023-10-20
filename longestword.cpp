#include <bits/stdc++.h>

using namespace std;

unordered_map<string, bool> cache;

bool isCompoundedWord(const string& word, const unordered_set<string>& wordSet) {
    if (cache.find(word) != cache.end()) {
        return cache[word];
    }

    for (int i = 1; i < word.length(); ++i) {
        string prefix = word.substr(0, i);
        if (wordSet.find(prefix) != wordSet.end()) {
            string suffix = word.substr(i);
            if (wordSet.find(suffix) != wordSet.end() || isCompoundedWord(suffix, wordSet)) {
                cache[word] = true;
                return true;
            }
        }
    }

    cache[word] = false;
    return false;
}

bool compareByLength(const string& a, const string& b) {
    return a.length() > b.length();
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    ifstream input_file("Input_02.txt");
    if (!input_file.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    vector<string> word_list;
    string current_word;

    while (getline(input_file, current_word)) {
        word_list.push_back(current_word);
    }

    input_file.close();

    unordered_set<string> word_set(word_list.begin(), word_list.end());
    sort(word_list.begin(), word_list.end(), compareByLength);
    string longest_compound;
    string second_longest_compound;

    for (const string& word : word_list) {
        if (isCompoundedWord(word, word_set)) {
            if (longest_compound.empty()) {
                longest_compound = word;
            } else if (word.length() > longest_compound.length()) {
                second_longest_compound = longest_compound;
                longest_compound = word;
            } else if (second_longest_compound.empty() || word.length() > second_longest_compound.length()) {
                second_longest_compound = word;
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto processing_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Longest Compound Word: " << longest_compound << endl;
    cout << "Second Longest Compound Word: " << second_longest_compound << endl;
    cout << "Time taken to process: " << processing_time.count() << " milliseconds" << endl;

    return 0;
}
