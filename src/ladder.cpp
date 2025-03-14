#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': "
         << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }

    if (str1.size() == str2.size()) {
        int differences = 0;
        for (size_t i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                differences++;
                if (differences > d) return false;
            }
        }
        return (differences <= d);
    } else {
        const string& longer  = (str1.size() > str2.size()) ? str1 : str2;
        const string& shorter = (str1.size() > str2.size()) ? str2 : str1;
        int countDiff = 0;
        size_t i = 0, j = 0;
        while (i < longer.size() && j < shorter.size()) {
            if (longer[i] != shorter[j]) {
                countDiff++;
                if (countDiff > 1) return false;
                i++;
            } else {
                i++;
                j++;
            }
        }
        if (i < longer.size()) countDiff++;
        return (countDiff <= 1);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word,
                                    const string& end_word,
                                    const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({ begin_word });

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_path = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_path.back();

        if (last_word == end_word) {
            return current_path;
        }

        for (auto &w : word_list) {
            if (is_adjacent(last_word, w) && visited.count(w) == 0) {
                visited.insert(w);
                vector<string> new_path = current_path;
                new_path.push_back(w);
                if (w == end_word) {
                    return new_path;
                }
                ladder_queue.push(new_path);
            }
        }
    }

    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        cerr << "Could not open file: " << file_name << endl;
        return;
    }
    string w;
    while (in >> w) {
        for (auto &c : w) {
            c = tolower(c);
        }
        word_list.insert(w);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
