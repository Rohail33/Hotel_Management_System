#include <iostream>
#include <string>
#include <vector>
using namespace std;
class RoomBooking {
private:
    int totalRooms;
    vector<int> roomNumbers;
    vector<string> roomTypes;
    vector<bool> isBooked;
    vector<string> customerNames;
public:
    RoomBooking(int totalRooms) {
        this->totalRooms = totalRooms;
        initializeRooms();
    }
    void initializeRooms() {
        for (int i = 1; i <= totalRooms; ++i) {
            roomNumbers.push_back(i);
            if (i <= totalRooms / 3) {
                roomTypes.push_back("Single");
            }
            else if (i <= (2 * totalRooms) / 3) {
                roomTypes.push_back("Double");
            }
            else {
                roomTypes.push_back("Suite");
            }
            isBooked.push_back(false);
            customerNames.push_back("");
        }
    }
    void displayAvailableRooms() {
        cout << "\nAvailable Rooms:\n";
        for (int i = 0; i < totalRooms; ++i) {
            if (!isBooked[i]) {
                cout << "Room Number: " << roomNumbers[i] << ", Room Type: " << roomTypes[i] << endl;
            }
        }
    }
    void bookRoom(int roomNumber, string customerName) {
        if (roomNumber < 1 || roomNumber > totalRooms) {
            cout << "Invalid room number!" << endl;
            return;
        }

        int index = roomNumber - 1;
        if (isBooked[index]) {
            cout << "Room " << roomNumber << " is already booked." << endl;
        }
        else {
            isBooked[index] = true;
            customerNames[index] = customerName;
            cout << "Room " << roomNumber << " successfully booked by " << customerName << "." << endl;
        }
    }
    void cancelBooking(int roomNumber) {
        if (roomNumber < 1 || roomNumber > totalRooms) {
            cout << "Invalid room number!" << endl;
            return;
        }
        int index = roomNumber - 1;
        if (!isBooked[index]) {
            cout << "Room " << roomNumber << " is not currently booked." << endl;
        }
        else {
            cout << "Booking for room " << roomNumber << " by " << customerNames[index] << " has been canceled." << endl;
            isBooked[index] = false;
            customerNames[index] = "";
        }
    }
    void displayBookedRooms() {
        cout << "\nBooked Rooms:\n";
        for (int i = 0; i < totalRooms; ++i) {
            if (isBooked[i]) {
                cout << "Room Number: " << roomNumbers[i] << ", Room Type: " << roomTypes[i]
                    << ", Customer: " << customerNames[i] << endl;
            }
        }
    }
};
int main() {
    int totalRooms;
    cout << "Enter the total number of rooms: ";
    cin >> totalRooms;
    RoomBooking bookingSystem(totalRooms);
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. Display Booked Rooms\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            bookingSystem.displayAvailableRooms();
            break;
        case 2: {
            int roomNumber;
            string customerName;
            cout << "Enter room number to book: ";
            cin >> roomNumber;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, customerName);
            bookingSystem.bookRoom(roomNumber, customerName);
            break;
        }
        case 3: {
            int roomNumber;
            cout << "Enter room number to cancel booking: ";
            cin >> roomNumber;
            bookingSystem.cancelBooking(roomNumber);
            break;
        }
        case 4:
            bookingSystem.displayBookedRooms();
            break;
        case 0:
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
