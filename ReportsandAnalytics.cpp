#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
using namespace std;
class ReportAnalytics{
    private:
    struct Transaction{
        string membersname;
        vector <pair<string,int>> items;
        double amount;
    };
    vector <Transaction> transactions;
    map <string,int> itemsales;
    double total_revenue;

    public:
    ReportAnalytics():total_revenue(0.0){}
    void customertransactions(const string &membersname,vector <pair<string,int>> &items,const double amount){
        transactions.push_back({membersname,items,amount});
        total_revenue+=amount;
        for(const auto &item: items){
            itemsales[item.first]+=item.second;
        }
    }

    void generatereport(){
        cout<<"******REPORT*******"<<endl;
        cout<<"Transactions= "<<transactions.size()<<endl;
        cout<<"Average Report= "<<(transactions.size()>0?total_revenue/transactions.size():0.0)<<endl;

        cout<<"\n***ITEMS SALES STATISTICS****"<<endl;
        cout<<left<<setw(20)<<"Item Name"<<"Item Quantity"<<endl;
        cout<<string(35,'-')<<endl;
        for(const auto &entry: itemsales){
            cout<<left<<setw(20)<<entry.first<<entry.second<<endl;
        }
    }

    void listtransaction(){
        cout<<"------TRANSACTIONS--------"<<endl;
        for(int i=0;i<transactions.size();++i){
            const auto &transaction=transactions[i];
            cout<<"Transactions: "<<i+1<<endl;
            cout<<"Customer: "<<transaction.membersname<<endl;
            cout<<"Items: "<<endl;
            for(const auto &items: transaction.items){
                cout<<"-"<<items.first<<"x"<<items.second<<endl;}
                cout<<"Total Amount: "<<fixed<<setprecision(2)<<transaction.amount;
                cout<<string(35,'-')<<endl;
            }
        }
    
    
    void resetanalytics(){
        transactions.clear();
        itemsales.clear();
        total_revenue=0.0;
    }
};
int main(){
ReportAnalytics analytics;
int choice;

do{
cout<<"\n-------Reports and Analytics Menu-------"<<endl;
cout<<"1.Record Transaction"<<endl;
cout<<"2.Generate Report"<<endl;
cout<<"3.List all Transactions"<<endl;
cout<<"4.Reset Analytics"<<endl;
cout<<"0.exit"<<endl;
cout<<"Enter your choice: ";
cin>>choice;

 switch (choice) {
            case 1: {
                string customerName;
                int itemCount;
                vector<pair<string, int>> items;
                double totalAmount;

                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);

                cout << "Enter number of items: ";
                cin >> itemCount;
                for (int i = 0; i < itemCount; ++i) {
                    string itemName;
                    int quantity;
                    cout << "Enter item name: ";
                    cin.ignore();
                    getline(cin, itemName);
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    items.push_back({itemName, quantity});
                }

                cout << "Enter total amount: ";
                cin >> totalAmount;

                analytics.customertransactions(customerName, items, totalAmount);
                break;
            }
            case 2:
                analytics.generatereport();
                break;
            case 3:
                analytics.listtransaction();
                break;
            case 4:
                analytics.resetanalytics();
                cout << "Analytics data has been reset." << endl;
                break;
            case 0:
                cout << "Exiting analytics system." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

return 0;
}