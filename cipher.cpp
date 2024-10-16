#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

// Function to encrypt or decrypt a text using Caesar Cipher
string caesarCipher(string text, int encryptionFlag, int key) {
    // Helper function to shift characters
    auto shiftChar = [](char c, int key, int direction) {
        if (isalpha(c)) { // Check if character is a letter
            char base = isupper(c) ? 'A' : 'a';
            // Shift the character and handle wrap-around using modulo 26
            return char((c - base + (key * direction) + 26) % 26 + base);
        }
        return c; // Non-alphabet characters remain unchanged
        };

    int direction = (encryptionFlag == 0) ? 1 : -1; // Direction: 1 for encryption, -1 for decryption
    string result = "";

    // Process each character of the text
    for (char c : text) {
        result += shiftChar(c, key, direction);
    }

    return result;
}

// Function to cluster grades into bins
void clusterGrades(const vector<int>& grades) {
    vector<int> clusters(11, 0); // 11 bins for grade ranges 0-9, 10-19, ..., 90-100

    // Count the grades in each cluster
    for (int grade : grades) {
        if (grade >= 0 && grade <= 100) {
            clusters[grade / 10]++;
        }
    }

    // Print the cluster counts
    cout << "Cluster counts: ";
    for (int count : clusters) {
        cout << count << " ";
    }
    cout << endl;
}

// Function to summarize a document (counts words, sentences, word frequencies)
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
    map<string, int> wordList;

    // Count sentences and words, while updating word frequencies
    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            numberOfSentences++;
        }
    }

    stringstream ss(text);
    string word;
    while (ss >> word) {
        numberOfWords++;
        wordList[word]++;
    }

    // Output the summary
    cout << "Number of sentences: " << numberOfSentences << endl;
    cout << "Number of words: " << numberOfWords << endl;
    cout << "Word frequencies: " << endl;
    for (const auto& entry : wordList) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

// Swap function using call by value (doesn't actually swap the original variables)
void swapv(int x, int y) {
    int aux = x;
    x = y;
    y = aux;
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

    // Count each word's frequency
    for (const string& word : list) {
        wordMap[word]++;
    }

    // Populate the output vectors
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
        cin.ignore();  // Clear newline character from input buffer
        getline(cin, text);
        cout << "Enter encryption flag (0 for encrypt, 1 for decrypt): ";
        cin >> encryptionFlag;
        cout << "Enter the key (positive integer): ";
        cin >> key;

        // Validate input
        if (key <= 0 || (encryptionFlag != 0 && encryptionFlag != 1)) {
            cout << "Invalid input." << endl;
        }
        else {
            // Perform Caesar cipher encryption or decryption
            string result = caesarCipher(text, encryptionFlag, key);
            cout << "Result: " << result << endl;
        }
    }
    else if (choice == 2) {
        // Task 2: Grade clustering
        vector<int> grades;
        int grade;
        cout << "Enter grades (enter -1 to stop): " << endl;
        while (cin >> grade && grade != -1) {
            grades.push_back(grade);
        }
        clusterGrades(grades);
    }
    else if (choice == 3) {
        // Task 3: Document summary
        string filename;
        cout << "Enter the filename: ";
        cin >> filename;
        documentSummary(filename);
    }
    else if (choice == 4) {
        // Swap functions
        int a, b;
        cout << "Enter two integers: ";
        cin >> a >> b;
        cout << "Before swapping: " << a << ", " << b << endl;

        // Using call by reference swap
        swapr(&a, &b);
        cout << "After swapping with swapr: " << a << ", " << b << endl;

        // Using function pointer to call swap
        void (*pf)(int&, int&) = swap;
        pf(a, b);
        cout << "After swapping with function pointer (swap): " << a << ", " << b << endl;
    }
    else if (choice == 5) {
        // Word statistics
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
}
