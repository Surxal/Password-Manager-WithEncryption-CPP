#include <iostream>
#include <fstream>

using namespace std;

// Encryption algorithm from chatgpt
string encryptCaesarCipher(string text, int shift) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char shiftedChar = text[i] + shift;

            if (islower(text[i]) && shiftedChar > 'z') {
                shiftedChar = 'a' + (shiftedChar - 'z' - 1);
            } else if (isupper(text[i]) && shiftedChar > 'Z') {
                shiftedChar = 'A' + (shiftedChar - 'Z' - 1);
            }

            result += shiftedChar;
        } else {
            result += text[i];
        }
    }

    return result;
}

// Decryption Algorithm from chatgpt
string decryptCaesarCipher(string encryptedText, int shift) {
    string result = "";

    for (int i = 0; i < encryptedText.length(); i++) {
        if (isalpha(encryptedText[i])) {
            char shiftedChar = encryptedText[i] - shift;

            if (islower(encryptedText[i]) && shiftedChar < 'a') {
                shiftedChar = 'z' - ('a' - shiftedChar - 1);
            } else if (isupper(encryptedText[i]) && shiftedChar < 'A') {
                shiftedChar = 'Z' - ('A' - shiftedChar - 1);
            }

            result += shiftedChar;
        } else {
            result += encryptedText[i]; // Keep non-alphabetic characters unchanged
        }
    }

    return result;
}


int main() {
    
    ofstream PassFile("pass.txt", ios::app);
    bool loop = true;
    int shift = 3;

    string addPass;
    string readText;

    cout << "Add a new password? (Y/S): ";
    cin >> addPass;

    ifstream MyReadFile("pass.txt");

    if (addPass == "Y" || addPass == "y") {
        string cmnd;
        cout << "Enter master password (show to show all passwords): ";
        cin >> cmnd;

        if (cmnd == "sss1234") {
            string identifier;
            string password;

            cout << "Type exit to exit" << endl;
            // while (loop == true){
                cout << "Password identifier?: ";
                cin >> identifier;
                cout << "";

                cout << "Enter Password: ";
                cin >> password;
                cout << "";

                string encryptedIdentifier = encryptCaesarCipher(identifier, shift);
                string encryptedPassword = encryptCaesarCipher(password, shift);
                
                PassFile << encryptedIdentifier << " : " << encryptedPassword << endl;

                cout << "Showing passwords (Decrypted form)" << endl;

                while (getline (MyReadFile, readText)) {
                    string decryptedIdentifier = decryptCaesarCipher(readText.substr(0, readText.find(":")), shift);
                    string decryptedPassword = decryptCaesarCipher(readText.substr(readText.find(":") + 1), shift);

                    cout << decryptedIdentifier << " : " << decryptedPassword << endl;
                }
                
            // }
        }
        else {
            cout << "Incorrect password!" << endl;
        }

    } else {
        cout << "Exiting...";
        loop = false;
    }

    PassFile.close();

    return 0;
}
