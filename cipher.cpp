#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Function to encrypt or decrypt text using Caesar Cipher
string caesarCipher(string text, int encryptionFlag, int key) {
    auto shiftChar = [](char c, int key, int direction) {
        if (isalpha(static_cast<unsigned char>(c))) { // Ensure safe cast
            char base = isupper(c) ? 'A' : 'a';
            return char((c - base + (key * direction) + 26) % 26 + base);
        }
        return c; // Non-alphabet characters remain unchanged
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
    for (int count : clusters) {
        cout << count << " ";
    }
    cout << endl;
}

// Function to summarize a document (counts words, sentences, word frequencies, and positions)
void documentSummary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    int numberOfSentences = 0;
    int numberOfWords = 0;
    map<string, int> wordFrequency;
    map<string, vector<int>> wordPositions;

    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            numberOfSentences++;
        }
    }

    stringstream ss(text);
    string word;
    int position = 1;

    while (ss >> word) {
        // Remove punctuation, ensure safe cast to unsigned char for non-ASCII characters
        word.erase(remove_if(word.begin(), word.end(),
            [](unsigned char c) { return ispunct(c); }), word.end());

        // Convert to lowercase safely
        transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c) { return tolower(c); });

        if (!word.empty()) {
            numberOfWords++;
            wordFrequency[word]++;
            wordPositions[word].push_back(position);
        }

        position++;
    }

    // Output the summary
    cout << "Number of sentences: " << numberOfSentences << endl;
    cout << "Number of words: " << numberOfWords << endl;
    cout << "Word frequencies and positions:" << endl;
    for (const auto& entry : wordFrequency) {
        cout << entry.first << ": " << entry.second << " times, positions: ";
        for (int pos : wordPositions[entry.first]) {
            cout << pos << " ";
        }
        cout << endl;
    }
}

// Swap function using call by pointer
void swapr(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

// Swap function using call by reference
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
    return find(listOfDistinctWords.begin(), listOfDistinctWords.end(), word) != listOfDistinctWords.end();
}

int main() {
    int choice;
    cout << "Select an option: " << endl;
    cout << "1. Caesar Cipher (encrypt/decrypt)" << endl;
    cout << "2. Grade Clustering" << endl;
    cout << "3. Document Summary" << endl;
    cout << "4. Swap Functions" << endl;
    cout << "5. Word Statistics" << endl;
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
        }
        else {
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
        cout << "After swapping with reference swap: " << a << ", " << b << endl;
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
        }
        else {
            cout << word << " is not found in the list." << endl;
        }
    }
    else {
        cout << "Invalid option." << endl;
    }

    return 0;
