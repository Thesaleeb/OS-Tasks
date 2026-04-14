#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Encrypt password using salt and 25 rounds
string encryptPassword(string password, int salt) {
    string encrypted = password;

    for (int round = 0; round < 25; round++) {
        for (int i = 0; i < encrypted.length(); i++) {
            encrypted[i] = encrypted[i] + (salt % 7) + 1;
        }
    }

    return encrypted;
}

// Check if password matches stored encrypted password
bool isValidPassword(string inputPassword, int salt, string storedPassword) {
    string encryptedInput = encryptPassword(inputPassword, salt);
    return encryptedInput == storedPassword;
}

int main() {
    vector<string> passwords = {
        "apple123", "hello456", "code789", "osproject",
        "network12", "secure99", "student55", "test123",
        "final2026", "report88"
    };

    vector<int> salts = {
        101, 202, 303, 404, 505,
        606, 707, 808, 909, 111
    };

    vector<string> encryptedPasswords;

    cout << "Generated Encrypted Passwords:\n";
    for (int i = 0; i < 10; i++) {
        string encrypted = encryptPassword(passwords[i], salts[i]);
        encryptedPasswords.push_back(encrypted);

        cout << "Password " << i + 1 << ": " << passwords[i]
             << " | Salt: " << salts[i]
             << " | Encrypted: " << encrypted << endl;
    }

    string inputPassword;
    int inputSalt;

    cout << "\nEnter password to check: ";
    cin >> inputPassword;

    cout << "Enter salt: ";
    cin >> inputSalt;

    bool found = false;

    for (int i = 0; i < encryptedPasswords.size(); i++) {
        if (isValidPassword(inputPassword, inputSalt, encryptedPasswords[i])) {
            found = true;
            break;
        }
    }

    if (found)
        cout << "Password is valid.\n";
    else
        cout << "Password is invalid.\n";

    return 0;
}