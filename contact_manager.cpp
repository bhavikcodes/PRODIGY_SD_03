#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Class to represent a Contact
class Contact {
private:
    string name;
    string phoneNumber;
    string email;

public:
    // Constructor
    Contact(string n, string p, string e) : name(n), phoneNumber(p), email(e) {}

    // Accessor methods
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }

    // Mutator methods
    void setName(const string& newName) { name = newName; }
    void setPhoneNumber(const string& newPhone) { phoneNumber = newPhone; }
    void setEmail(const string& newEmail) { email = newEmail; }

    // Display contact details
    void displayContact() const {
        cout << "Name: " << name << ", Phone: " << phoneNumber << ", Email: " << email << endl;
    }

    // Save contact to file
    void saveToFile(ofstream &out) const {
        out << name << "\n" << phoneNumber << "\n" << email << "\n";
    }

    // Load contact from file
    static Contact loadFromFile(ifstream &in) {
        string n, p, e;
        getline(in, n);
        getline(in, p);
        getline(in, e);
        return Contact(n, p, e);
    }
};

// Class to manage a list of Contacts
class ContactManager {
private:
    vector<Contact> contacts;

    // Load contacts from a file
    void loadContacts() {
        ifstream file("contacts.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                Contact c = Contact::loadFromFile(file);
                if (!c.getName().empty()) { // To avoid empty entries at end of file
                    contacts.push_back(c);
                }
            }
            file.close();
        }
    }

    // Save contacts to a file
    void saveContacts() {
        ofstream file("contacts.txt");
        if (file.is_open()) {
            for (const auto& c : contacts) {
                c.saveToFile(file);
            }
            file.close();
        }
    }

public:
    // Constructor
    ContactManager() {
        loadContacts();
    }

    // Destructor
    ~ContactManager() {
        saveContacts();
    }

    // Add a new contact
    void addContact() {
        string name, phone, email;
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter phone number: ";
        getline(cin, phone);
        cout << "Enter email address: ";
        getline(cin, email);
        contacts.push_back(Contact(name, phone, email));
        cout << "Contact added successfully!\n";
    }

    // View all contacts
    void viewContacts() const {
        if (contacts.empty()) {
            cout << "No contacts available.\n";
            return;
        }
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << i + 1 << ". ";
            contacts[i].displayContact();
        }
    }

    // Edit an existing contact
    void editContact() {
        viewContacts();
        if (contacts.empty()) return;

        int index;
        cout << "Enter the contact number to edit: ";
        cin >> index;

        if (index < 1 || index > contacts.size()) {
            cout << "Invalid contact number!\n";
            return;
        }

        string name, phone, email;
        cout << "Enter new name: ";
        getline(cin >> ws, name);
        cout << "Enter new phone number: ";
        getline(cin, phone);
        cout << "Enter new email address: ";
        getline(cin, email);

        contacts[index - 1].setName(name);
        contacts[index - 1].setPhoneNumber(phone);
        contacts[index - 1].setEmail(email);
        cout << "Contact updated successfully!\n";
    }

    // Delete a contact
    void deleteContact() {
        viewContacts();
        if (contacts.empty()) return;

        int index;
        cout << "Enter the contact number to delete: ";
        cin >> index;

        if (index < 1 || index > contacts.size()) {
            cout << "Invalid contact number!\n";
            return;
        }

        contacts.erase(contacts.begin() + index - 1);
        cout << "Contact deleted successfully!\n";
    }
};

int main() {
    ContactManager manager;
    int choice;

    do {
        cout << "\nContact Manager Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.viewContacts();
                break;
            case 3:
                manager.editContact();
                break;
            case 4:
                manager.deleteContact();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
