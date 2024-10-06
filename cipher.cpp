#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

string caesarCipher(string text, int encryptionFlag, int key) {
    auto shiftChar = [](char c, int key, int direction) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            return char((c - base + (key * direction) + 26) % 26 + base);
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

void clusterGrades() {
    vector<int> grades = { 100, 98, 15, 30, 25, 70, 82, 66, 78, 40 };
    vector<int> clusters(11, 0);

    for (int grade : grades) {
        if (grade >= 0 && grade <= 100) {
            clusters[grade / 10]++;
        }
    }

    cout << "Cluster counts: ";
    for (int count : clusters) {
        cout << count;
    }
    cout << endl;
}
void documentSummary() {
    string filename = "input.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text;
    string line;
    while (getline(file, line)) {
        text += line + " ";
    }

    file.close();

    int numberOfSentences = 0;
    int numberOfWords = 0;
    map<string, int> wordList;

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

    cout << "Number of sentences: " << numberOfSentences << endl;
    cout << "Number of words: " << numberOfWords << endl;
    cout << "Word frequencies: " << endl;
    for (const auto& entry : wordList) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

int main() {
    int choice;
    cout << "Select an option: " << endl;
    cout << "1. Caesar Cipher (encrypt/decrypt)" << endl;
    cout << "2. Grade Clustering" << endl;
    cout << "3. Document Summary" << endl;
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

        // Validate the input for encryption flag and key
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
        // Task 1: Grade clustering
        clusterGrades();
    }
    else if (choice == 3) {
        // Task 2: Document summary
        documentSummary();
    }
    else {
        cout << "Invalid option." << endl;
    }

    return 0;
}
