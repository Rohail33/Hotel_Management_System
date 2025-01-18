#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <map>
using namespace std;
// Customer Class ( Refer to the Customer_Managment Module if needed a seprate example )
class Customer {
public:
    int id;
    string name;
    string contactNumber;
    string email;
    Customer(int id = 0, const string& name = "", const string& contactNumber = "", const string& email = "")
        : id(id), name(name), contactNumber(contactNumber), email(email) {
    }
    string toString() const {
        return to_string(id) + "," + name + "," + contactNumber + "," + email + "\n";
    }
    static Customer fromString(const string& data) {
        Customer customer;
        size_t pos = 0, prev = 0;
        int field = 0;
        while ((pos = data.find(',', prev)) != string::npos) {
            string token = data.substr(prev, pos - prev);
            switch (field) {
            case 0: customer.id = stoi(token); break;
            case 1: customer.name = token; break;
            case 2: customer.contactNumber = token; break;
            }
            prev = pos + 1;
            field++;
        }
        customer.email = data.substr(prev);
        return customer;
    }
};

// CustomerManager Class ( Refer to the Customer_Managment Module if needed a seprate example )
class CustomerManager {
private:
    vector<Customer> customers;
    int nextCustomerId;
    void saveToFile() {
        ofstream file("customers.txt");
        if (file.is_open()) {
            for (const auto& customer : customers) {
                file << customer.toString();
            }
            file.close();
        }
        else {
            cerr << "Error saving customer data to file!" << endl;
        }
    }
    void loadFromFile() {
        ifstream file("customers.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                customers.push_back(Customer::fromString(line));
            }
            file.close();
        }
        else {
            cerr << "Error loading customer data from file!" << endl;
        }

        if (!customers.empty()) {
            nextCustomerId = customers.back().id + 1;
        }
    }
public:
    CustomerManager() : nextCustomerId(1) { loadFromFile(); }

    void addCustomer(const string& name, const string& contactNumber, const string& email) {
        customers.emplace_back(nextCustomerId++, name, contactNumber, email);
        saveToFile();
        cout << "Customer added successfully!" << endl;
    }
    void displayCustomers() const {
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
};

// RoomBooking Class ( Refer to the Romm Booking Module if needed a seprate example )
class RoomBooking {
private:
    struct Room {
        int number;
        string type;
        bool isBooked;
        string customerName;

        Room(int num, const string& t, bool booked, const string& customer)
            : number(num), type(t), isBooked(booked), customerName(customer) {
        }
    };
    vector<Room> rooms;
public:
    RoomBooking(int totalRooms) {
        for (int i = 1; i <= totalRooms; ++i) {
            string type = (i <= totalRooms / 3) ? "Single" : (i <= 2 * totalRooms / 3) ? "Double" : "Suite";
            rooms.emplace_back(i, type, false, "");
        }
    }
    void displayAvailableRooms() {
        cout << "\nAvailable Rooms:\n";
        for (const auto& room : rooms) {
            if (!room.isBooked) {
                cout << "Room Number: " << room.number << ", Room Type: " << room.type << endl;
            }
        }
    }
    void bookRoom(int roomNumber, const string& customerName) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!" << endl;
            return;
        }
        Room& room = rooms[roomNumber - 1];
        if (room.isBooked) {
            cout << "Room " << roomNumber << " is already booked." << endl;
        }
        else {
            room.isBooked = true;
            room.customerName = customerName;
            cout << "Room " << roomNumber << " successfully booked by " << customerName << "." << endl;
        }
    }
    void cancelBooking(int roomNumber) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!" << endl;
            return;
        }
        Room& room = rooms[roomNumber - 1];
        if (!room.isBooked) {
            cout << "Room " << roomNumber << " is not currently booked." << endl;
        }
        else {
            cout << "Booking for room " << roomNumber << " by " << room.customerName << " has been canceled." << endl;
            room.isBooked = false;
            room.customerName = "";
        }
    }
    void displayBookedRooms() {
        cout << "\nBooked Rooms:\n";
        for (const auto& room : rooms) {
            if (room.isBooked) {
                cout << "Room Number: " << room.number << ", Room Type: " << room.type
                    << ", Customer: " << room.customerName << endl;
            }
        }
    }
};

// Bill Class ( Refer to the Payment&Billing Module if needed a seprate example )
class Bill {
private:
    struct Item {
        string name;
        double price;
        int quantity;
    };
    vector<Item> items;
    double totalAmount;
    double discount;
public:
    Bill() : totalAmount(0.0), discount(0.0) {}
    void addItem(const string& itemName, double price, int quantity) {
        items.push_back({ itemName, price, quantity });
        totalAmount += price * quantity;
    }
    void displayBill() {
        cout << "\n========== BILL ==========\n";
        cout << left << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Qty" << setw(15) << "Total" << endl;
        cout << string(55, '-') << endl;
        for (const auto& item : items) {
            cout << left << setw(20) << item.name
                << setw(10) << item.price
                << setw(10) << item.quantity
                << setw(15) << item.price * item.quantity << endl;
        }
        cout << string(55, '-') << endl;
        cout << "Subtotal: " << totalAmount << endl;
        cout << "Discount: " << discount << endl;
        cout << "Grand Total: " << totalAmount - discount << endl;
    }
    void applyDiscount(double discountPercentage) {
        discount = (discountPercentage / 100) * totalAmount;
    }
    double getTotal() const {
        return totalAmount - discount;
    }
    void reset() {
        items.clear();
        totalAmount = 0.0;
        discount = 0.0;
    }
};

// ReportAnalytics Class ( Refer to the Report&Analytics Module if needed a seprate example )
class ReportAnalytics {
private:
    struct Transaction {
        string customerName;
        vector<pair<string, int>> items;
        double totalAmount;
    };
    vector<Transaction> transactions;
    map<string, int> itemSales;
    double totalRevenue;
public:
    ReportAnalytics() : totalRevenue(0.0) {}
    void recordTransaction(const string& customerName, const vector<pair<string, int>>& items, double totalAmount) {
        transactions.push_back({ customerName, items, totalAmount });
        totalRevenue += totalAmount;
        for (const auto& item : items) {
            itemSales[item.first] += item.second;
        }
    }
    void generateReport() {
        cout << "\n======= REPORT =======\n";
        cout << "Total Transactions: " << transactions.size() << endl;
        cout << "Total Revenue: " << totalRevenue << endl;

        cout << "\nItem Sales:\n";
        for (const auto& entry : itemSales) {
            cout << entry.first << ": " << entry.second << " units sold\n";
        }
    }
};
int main() {
    int totalRooms = 10;
    CustomerManager customerManager;
    RoomBooking roomBooking(totalRooms);
    Bill bill;
    ReportAnalytics analytics;
    int choice;
    do {
        cout << "\n===== Hotel Management System =====\n";
        cout << "1. Manage Customers\n";
        cout << "2. Manage Rooms\n";
        cout << "3. Manage Billing\n";
        cout << "4. Generate Reports\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int subChoice;
            cout << "\nCustomer Management:\n";
            cout << "1. Add Customer\n";
            cout << "2. Display Customers\n";
            cout << "Enter your choice: ";
            cin >> subChoice;
            if (subChoice == 1) {
                string name, contact, email;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter contact number: ";
                getline(cin, contact);
                cout << "Enter email: ";
                getline(cin, email);
                customerManager.addCustomer(name, contact, email);
            }
            else if (subChoice == 2) {
                customerManager.displayCustomers();
            }
            else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 2: {
            int subChoice;
            cout << "\nRoom Management:\n";
            cout << "1. Display Available Rooms\n";
            cout << "2. Book a Room\n";
            cout << "3. Cancel Booking\n";
            cout << "4. Display Booked Rooms\n";
            cout << "Enter your choice: ";
            cin >> subChoice;
            if (subChoice == 1) {
                roomBooking.displayAvailableRooms();
            }
            else if (subChoice == 2) {
                int roomNumber;
                string customerName;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                roomBooking.bookRoom(roomNumber, customerName);
            }
            else if (subChoice == 3) {
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                roomBooking.cancelBooking(roomNumber);
            }
            else if (subChoice == 4) {
                roomBooking.displayBookedRooms();
            }
            else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 3: {
            int subChoice;
            cout << "\nBilling Management:\n";
            cout << "1. Add Item to Bill\n";
            cout << "2. Display Bill\n";
            cout << "3. Apply Discount\n";
            cout << "Enter your choice: ";
            cin >> subChoice;
            if (subChoice == 1) {
                string itemName;
                double price;
                int quantity;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, itemName);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                bill.addItem(itemName, price, quantity);
            }
            else if (subChoice == 2) {
                bill.displayBill();
            }
            else if (subChoice == 3) {
                double discount;
                cout << "Enter discount percentage: ";
                cin >> discount;
                bill.applyDiscount(discount);
            }
            else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 4:
            analytics.generateReport();
            break;
        case 5:
            cout << "Exiting system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
