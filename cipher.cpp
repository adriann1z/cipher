#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

// Function to encrypt or decrypt a text using Caesar Cipher
string caesarCipher(string text, int encryptionFlag, int key) {
    auto shiftChar = [](char c, int key, int direction) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            const int ALPHABET_SIZE = 26;
            return char((c - base + (key * direction) + ALPHABET_SIZE) % ALPHABET_SIZE + base);
        }
        return c;
    };

    int direction = (encryptionFlag == 0) ? 1 : -1;
    string result = "";
    for (char c : text) {
        result += shiftChar(c, key, direction);
    }
    return result;
}

// Function to cluster grades into bins
void clusterGrades(const vector<int>& grades) {
    vector<int> clusters(11, 0);
    for (int grade : grades) {
        if (grade >= 0 && grade <= 100) {
            clusters[grade / 10]++;
        }
    }
    cout << "Cluster counts: ";
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << i * 10 << "-" << (i * 10 + 9) << ": " << clusters[i] << " ";
    }
    cout << endl;
}

// Function to summarize a document (counts sentences, words, word frequencies, and word positions)
void documentSummary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string text, line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    int numberOfSentences = 0;
    int wordPosition = 1;
    map<string, int> wordFrequencies;
    map<string, vector<int>> wordPositions;

    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            numberOfSentences++;
        }
    }

    transform(text.begin(), text.end(), text.begin(), ::tolower);

    stringstream ss(text);
    string word;

    while (ss >> word) {
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalnum(c); }), word.end());
        if (!word.empty()) {
            wordFrequencies[word]++;
            wordPositions[word].push_back(wordPosition);
            wordPosition++;
        }
    }

    cout << "Number of sentences: " << numberOfSentences << endl;
    cout << "Total number of words: " << wordPosition - 1 << endl;
    cout << "Word frequencies and positions: " << endl;
    for (const auto& entry : wordFrequencies) {
        cout << entry.first << ": " << entry.second << " (positions: ";
        for (int pos : wordPositions[entry.first]) {
            cout << pos << " ";
        }
        cout << ")" << endl;
    }
}

// Swap functions
void swapv(int x, int y) {
    int aux = x;
    x = y;
    y = aux;
}

void swapr(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void swap(int& x, int& y) {
    int aux = x;
    x = y;
    y = aux;
}

// Function to get statistics of word frequencies
void getStatistics(const vector<string>& list, vector<string>& listOfDistinctWords, vector<int>& listOfCounts) {
    map<string, int> wordMap;
    for (const string& word : list) {
        wordMap[word]++;
    }
    for (const auto& entry : wordMap) {
        listOfDistinctWords.push_back(entry.first);
        listOfCounts.push_back(entry.second);
    }
}

// Function to search for a word in a list of words
bool searchWord(const vector<string>& listOfDistinctWords, const string& word) {
    for (const string& distinctWord : listOfDistinctWords) {
        if (distinctWord == word) {
            return true;
        }
    }
    return false;
}

int main() {
    int choice;
    do {
        cout << "Select an option: " << endl;
        cout << "1. Caesar Cipher (encrypt/decrypt)" << endl;
        cout << "2. Grade Clustering" << endl;
        cout << "3. Document Summary" << endl;
        cout << "4. Swap Functions" << endl;
        cout << "5. Word Statistics" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            string text;
            int encryptionFlag, key;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter encryption flag (0 for encrypt, 1 for decrypt): ";
            cin >> encryptionFlag;
            cout << "Enter the key (positive integer): ";
            cin >> key;
            if (key <= 0 || (encryptionFlag != 0 && encryptionFlag != 1)) {
                cout << "Invalid input." << endl;
            } else {
                string result = caesarCipher(text, encryptionFlag, key);
                cout << "Result: " << result << endl;
            }
        }
        else if (choice == 2) {
            vector<int> grades;
            int grade;
            cout << "Enter grades (enter -1 to stop): " << endl;
            while (cin >> grade && grade != -1) {
                grades.push_back(grade);
            }
            clusterGrades(grades);
        }
        else if (choice == 3) {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            documentSummary(filename);
        }
        else if (choice == 4) {
            int a, b;
            cout << "Enter two integers: ";
            cin >> a >> b;
            cout << "Before swapping: " << a << ", " << b << endl;
            swapr(&a, &b);
            cout << "After swapping with swapr: " << a << ", " << b << endl;
            swap(a, b);
            cout << "After swapping with function pointer (swap): " << a << ", " << b << endl;
        }
        else if (choice == 5) {
            vector<string> list;
            string word;
            cout << "Enter words (enter 'done' to finish): " << endl;
            while (cin >> word && word != "done") {
                list.push_back(word);
            }
            vector<string> listOfDistinctWords;
            vector<int> listOfCounts;
            getStatistics(list, listOfDistinctWords, listOfCounts);
            cout << "Word statistics:" << endl;
            for (size_t i = 0; i < listOfDistinctWords.size(); ++i) {
                cout << listOfDistinctWords[i] << ": " << listOfCounts[i] << endl;
            }
            cout << "Enter a word to search: ";
            cin >> word;
            if (searchWord(listOfDistinctWords, word)) {
                cout << word << " is found in the list." << endl;
            } else {
                cout << word << " is not found in the list." << endl;
            }
        }
        else if (choice == 6) {
            cout << "Exiting the program." << endl;
        }
        else {
            cout << "Invalid option." << endl;
        }
    } while (choice != 6);

    return 0;
}

