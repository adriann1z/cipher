#include <iostream>
#include <string>
using namespace std;

// Function to encrypt or decrypt a text using Caesar Cipher
string caesarCipher(string text, int encryptionFlag, int key) {
    // Helper function to shift characters
    auto shiftChar = [](char c, int key, int direction) {
        if (isalpha(c)) {  // Check if character is a letter
            char base = isupper(c) ? 'A' : 'a';
            // Shift the character and handle wrap-around using modulo 26
            return char((c - base + (key * direction) + 26) % 26 + base);
        }
        return c;  // Non-alphabet characters remain unchanged
        };

    int direction = (encryptionFlag == 0) ? 1 : -1;  // Direction: 1 for encryption, -1 for decryption
    string result = "";

    // Process each character of the text
    for (char c : text) {
        result += shiftChar(c, key, direction);
    }

    return result;
}

int main() {
    string text;
    int encryptionFlag;
    int key;

    // Input the text, encryption flag, and key
    cout << "Enter the text: ";
    getline(cin, text);  // Use getline to support spaces in input

    cout << "Enter encryption flag (0 for encrypt, 1 for decrypt): ";
    cin >> encryptionFlag;

    // Check for valid flag (either 0 or 1)
    if (encryptionFlag != 0 && encryptionFlag != 1)
    {
        cout << "Invalid encryption flag. Must be 0 or 1." << endl;
        return 1;  // Exit with error
    }

    cout << "Enter the key (positive integer): ";
    cin >> key;

    // Ensure key is a positive integer
    if (key <= 0) {
        cout << "Invalid key. Must be a positive integer." << endl;
        return 1;  // Exit with error
    }

    // Call the Caesar cipher function and print the result
    string result = caesarCipher(text, encryptionFlag, key);
    cout << "Result: " << result << endl;

    return 0;
}
