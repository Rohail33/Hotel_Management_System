#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Room {
public:
    int room_number;
    string room_type;
    bool availiability;
    double price;
    Room(int number = 0, string type = "", bool available = true, double cost = 0.0)
        : room_number(number), room_type(type), availiability(available), price(cost) {
    }
    string toString() const {
        return to_string(room_number) + "," + room_type + "," +
            (availiability ? "1" : "0") + "," + to_string(price) + "\n";
    }
    static Room fromString(const string& data) {
        Room room;
        size_t pos = 0, prev = 0;
        int field = 0;

        while ((pos = data.find(',', prev)) != string::npos) {
            string token = data.substr(prev, pos - prev);
            switch (field) {
            case 0: room.room_number = stoi(token); break;
            case 1: room.room_type = token; break;
            case 2: room.availiability = (token == "1"); break;
            }
            prev = pos + 1;
            field++;
        }
        room.price = stod(data.substr(prev));
        return room;
    }
};
class Customer {
public:
    int customerId;
    string name;
    int loyalty_points;
    Customer(int id = 0, string person = "", int loyalty = 0)
        : customerId(id), name(person), loyalty_points(loyalty) {
    }
    string toString() const {
        return to_string(customerId) + "," + name + "," + to_string(loyalty_points) + "\n";
    }
    static Customer fromString(const string& data) {
        Customer customer;
        size_t pos = 0, prev = 0;
        int field = 0;
        while ((pos = data.find(',', prev)) != string::npos) {
            string token = data.substr(prev, pos - prev);
            switch (field) {
            case 0: customer.customerId = stoi(token); 
                break;
            case 1: customer.name = token; 
                break;
            }
            prev = pos + 1;
            field++;
        }
        customer.loyalty_points = stoi(data.substr(prev));
        return customer;
    }
};
template <typename T>
void save_file(const string& filename, const vector<T>& objects) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& obj : objects) {
            file << obj.toString();
        }
        file.close();
        cout << "Data saved successfully to " << filename << endl;
    }
    else {
        cerr << "Error opening file for writing!" << endl;
    }
}
template <typename T>
vector<T> load_file(const string& filename, T(*fromString)(const string&)) {
    vector<T> objects;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            objects.push_back(fromString(line));
        }
        file.close();
        cout << "Data loaded successfully from " << filename << endl;
    }
    else {
        cerr << "Error opening file for reading!" << endl;
    }
    return objects;
}
int main() {
    /* Exapmple Data has been defined here for Room and Customer Class.
       You can also extract data from other files and Put it inside the vector customers and rooms.
       This is a general Base which would be used in the Final Project File (With some modifications).
    */
    vector<Room> rooms = {
        Room(101, "Single", true, 50.0),
        Room(102, "Double", false, 75.0),
        Room(103, "Suite", true, 120.0)
    };
    vector<Customer> customers = {
        Customer(1, "John Doe", 150),
        Customer(2, "Jane Smith", 200)
    };
    save_file("rooms.txt", rooms);
    save_file("customers.txt", customers);
    vector<Room> loadedRooms = load_file("rooms.txt", Room::fromString);
    vector<Customer> loadedCustomers = load_file("customers.txt", Customer::fromString);
    cout << "\nLoaded Rooms:\n";
    for (const auto& room : loadedRooms) {
        cout << "Room " << room.room_number << " (" << room.room_type
            << "), Available: " << (room.availiability ? "Yes" : "No")
            << ", Price: $" << room.price << endl;
    }
    cout << "\nLoaded Customers:\n";
    for (const auto& customer : loadedCustomers) {
        cout << "Customer ID: " << customer.customerId << ", Name: " << customer.name
            << ", Loyalty Points: " << customer.loyalty_points << endl;
    }
}
