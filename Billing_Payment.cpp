#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
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
    double amountPaid;

public:
    Bill() : totalAmount(0.0), discount(0.0), amountPaid(0.0) {}

    void addItem(const string &itemName, double price, int quantity) {
        items.push_back({itemName, price, quantity});
        totalAmount += price * quantity;
    }

    void displayBill() {
        cout << "\n========== BILL ==========" << endl;
        cout << left << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Qty" << setw(15) << "Total" << endl;
        cout << string(55, '-') << endl;
        for (const auto &item : items) {
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

    void processPayment(double payment) {
        double grandTotal = totalAmount - discount;
        if (payment < grandTotal) {
            cout << "Insufficient payment. Remaining balance: " << grandTotal - payment << endl;
        } else {
            amountPaid = payment;
            cout << "Payment successful! Change: " << payment - grandTotal << endl;
        }
    }

    void resetBill() {
        items.clear();
        totalAmount = 0.0;
        discount = 0.0;
        amountPaid = 0.0;
    }
};

int main() {
    Bill bill;
    int choice;

    do {
        cout << "\n====== Billing Menu ======" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Display Bill" << endl;
        cout << "3. Apply Discount" << endl;
        cout << "4. Process Payment" << endl;
        cout << "5. Reset Bill" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int qty;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter item price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> qty;
                bill.addItem(name, price, qty);
                break;
            }
            case 2:
                bill.displayBill();
                break;
            case 3: {
                double discount;
                cout << "Enter discount percentage: ";
                cin >> discount;
                bill.applyDiscount(discount);
                break;
            }
            case 4: {
                double payment;
                cout << "Enter payment amount: ";
                cin >> payment;
                bill.processPayment(payment);
                break;
            }
            case 5:
                bill.resetBill();
                cout << "Bill has been reset." << endl;
                break;
            case 0:
                cout << "Exiting billing system." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
