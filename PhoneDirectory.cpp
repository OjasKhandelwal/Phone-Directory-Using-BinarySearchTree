#include <iostream>
#include <string>
#include <cctype>  // for isdigit
using namespace std;

struct Contact {
    string name, phone;
    Contact *left, *right;
};

Contact* createContact(string name, string phone) {
    Contact* newNode = new Contact;
    newNode->name = name;
    newNode->phone = phone;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Contact* insert(Contact* root, string name, string phone) {
    if (!root) return createContact(name, phone);
    if (name < root->name)
        root->left = insert(root->left, name, phone);
    else if (name > root->name)
        root->right = insert(root->right, name, phone);
    else
        cout << "Contact with this name already exists!\n";
    return root;
}

Contact* search(Contact* root, string name) {
    if (!root || root->name == name) return root;
    return (name < root->name) ? search(root->left, name) : search(root->right, name);
}

Contact* findMin(Contact* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Contact* remove(Contact* root, string name) {
    if (!root) return nullptr;
    if (name < root->name)
        root->left = remove(root->left, name);
    else if (name > root->name)
        root->right = remove(root->right, name);
    else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left) {
            Contact* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Contact* temp = root->left;
            delete root;
            return temp;
        } else {
            Contact* temp = findMin(root->right);
            root->name = temp->name;
            root->phone = temp->phone;
            root->right = remove(root->right, temp->name);
        }
    }
    return root;
}

void inorder(Contact* root) {
    if (!root) return;
    inorder(root->left);
    cout << "Name: " << root->name << " | Phone: " << root->phone << endl;
    inorder(root->right);
}

// Function to validate if the phone number is exactly 10 digits
bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    Contact* root = nullptr;
    int choice;
    string name, phone;

    do {
        cout << "\n===== PHONE DIRECTORY MENU =====\n"
             << "1. Add Contact\n"
             << "2. Search Contact\n"
             << "3. Delete Contact\n"
             << "4. Display All Contacts\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);

                // Loop until a valid phone number is entered
                do {
                    cout << "Enter phone number (10 digits): ";
                    getline(cin, phone);

                    if (!isValidPhoneNumber(phone)) {
                        cout << "Invalid phone number! It must be exactly 10 digits.\n";
                    }
                } while (!isValidPhoneNumber(phone));

                root = insert(root, name, phone);
                cout << "Contact added successfully!\n";
                break;

            case 2: {
                cout << "Enter name to search: ";
                getline(cin, name);
                Contact* found = search(root, name);
                if (found)
                    cout << "Found! " << found->name << " -> " << found->phone << endl;
                else
                    cout << "Contact not found!\n";
                break;
            }

            case 3:
                cout << "Enter name to delete: ";
                getline(cin, name);
                root = remove(root, name);
                cout << "Contact deleted (if it existed).\n";
                break;

            case 4:
                cout << "\n--- Phone Directory (Alphabetical Order) ---\n";
                inorder(root);
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}
