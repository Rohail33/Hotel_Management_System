#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class Customer {
public:
    int id;
    string name;
    string contactNumber;
    string email;

    Customer(int id, const string& name, const string& contactNumber, const string& email)
        : id(id), name(name), contactNumber(contactNumber), email(email) {}
};
class CustomerManager {
private:
    vector<Customer> customers;
    int nextCustomerId;

public:
    CustomerManager() : nextCustomerId(1) {}

    void addCustomer(const string& name, const string& contactNumber, const string& email) {
        customers.emplace_back(nextCustomerId++, name, contactNumber, email);
        cout << "Customer added successfully!" << endl;
    }

    void displayCustomers() {
        if (customers.empty()) {
            cout << "No customers available." << endl;
            return;
        }

        cout << "\n========== Customers ==========" << endl;
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << setw(30) << "Email" << endl;
        cout << string(70, '-') << endl;
        for (const auto& customer : customers) {
            cout << left << setw(5) << customer.id
                << setw(20) << customer.name
                << setw(15) << customer.contactNumber
                << setw(30) << customer.email << endl;
        }
    }

    void updateCustomer(int id) {
        for (auto& customer : customers) {
            if (customer.id == id) {
                cout << "Enter new name (current: " << customer.name << "): ";
                cin.ignore();
                getline(cin, customer.name);

                cout << "Enter new contact number (current: " << customer.contactNumber << "): ";
                getline(cin, customer.contactNumber);

                cout << "Enter new email (current: " << customer.email << "): ";
                getline(cin, customer.email);

                cout << "Customer updated successfully!" << endl;
                return;
            }
        }
        cout << "Customer with ID " << id << " not found." << endl;
    }

    void deleteCustomer(int id) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->id == id) {
                customers.erase(it);
                cout << "Customer deleted successfully!" << endl;
                return;
            }
        }
        cout << "Customer with ID " << id << " not found." << endl;
    }
};

int main() {
    CustomerManager customerManager;
    int choice;

    do {
        cout << "\n====== Customer Management Menu ======" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Display Customers" << endl;
        cout << "3. Update Customer" << endl;
        cout << "4. Delete Customer" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, contact, email;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter contact number: ";
            getline(cin, contact);
            cout << "Enter email address: ";
            getline(cin, email);
            customerManager.addCustomer(name, contact, email);
            break;
        }
        case 2:
            customerManager.displayCustomers();
            break;
        case 3: {
            int id;
            cout << "Enter customer ID to update: ";
            cin >> id;
            customerManager.updateCustomer(id);
            break;
        }
        case 4: {
            int id;
            cout << "Enter customer ID to delete: ";
            cin >> id;
            customerManager.deleteCustomer(id);
            break;
        }
        case 0:
            cout << "Exiting customer management system." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
