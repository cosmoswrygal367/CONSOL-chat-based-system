#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int MAX_USERS = 10;
string fileName = "users.txt";

// Function declarations
int registeredUsers();
bool usernameExists(const string& username);
void registerUser();
void showMenu();

// Count registered users
int registeredUsers() {
    ifstream file(fileName);
    string line;
    int count = 0;

    if (!file.is_open()) {
        return 0;
    }

    while (getline(file, line)) {
        count++;
    }
    file.close();
    return count;
}

// Check if username already exists
bool usernameExists(const string& username) {
    ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }
    string line;
    while (getline(file, line)) {
        string existingUsername = line.substr(0, line.find(','));
        if (existingUsername == username) {
            return true;
        }
    }
    file.close();
    return false;
}

// Register a new user
void registerUser() {
    if (registeredUsers() >= MAX_USERS) {
        cout << "Registration full. Try again later.\n";
        return;
    }

    string username, password;
    cout << "\nEnter your username: ";
    cin >> username;

    if (usernameExists(username)) {
        cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    cout << "Enter your password: ";
    cin >> password;

    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    file << username << "," << password << "\n";
    file.close();
    cout << "You have been registered successfully!\n";
}

// Main menu
void showMenu() {
    int choice;
    while (true) {
        cout << "\n=== Chat System ===\n";
        cout << "1. Register\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                cout << "Exiting program...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

int main() {
    showMenu();
    return 0;
}
