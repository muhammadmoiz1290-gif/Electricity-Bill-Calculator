#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ==================== Node for Linked List (Customer Record) ====================
struct Customer {
    int id;
    string name;
    int units;
    double billAmount;
    Customer* next;

    Customer(int cid, string cname, int cunits) {
        id = cid;
        name = cname;
        units = cunits;
        billAmount = 0.0;
        next = nullptr;
    }
};

// ==================== Electricity Bill Calculator Class ====================
class ElectricityBillSystem {
private:
    // Arrays for tariff structure
    double tariffRates[5];   // Slab rates
    int slabLimits[4];       // Slab unit limits

    // Linked list head
    Customer* head;
    int customerCount;

public:
    ElectricityBillSystem() {
        head = nullptr;
        customerCount = 0;

        // Tariff rates
        tariffRates[0] = 5.0;   // 0–100 units
        tariffRates[1] = 7.0;   // 101–300 units
        tariffRates[2] = 10.0;  // 301–500 units
        tariffRates[3] = 15.0;  // 501–1000 units
        tariffRates[4] = 20.0;  // Above 1000 units

        // Slab limits
        slabLimits[0] = 100;
        slabLimits[1] = 300;
        slabLimits[2] = 500;
        slabLimits[3] = 1000;
    }

    // Calculate electricity bill
    double calculateBill(int units) {
        double total = 0.0;
        int remaining = units;

        for (int i = 0; i < 5; i++) {
            if (remaining <= 0)
                break;

            int slabSize;
            if (i == 0) {
                slabSize = slabLimits[0];
            } else if (i < 4) {
                slabSize = slabLimits[i] - slabLimits[i - 1];
            } else {
                slabSize = remaining;
            }

            int unitsInSlab = (remaining < slabSize) ? remaining : slabSize;
            total += unitsInSlab * tariffRates[i];
            remaining -= unitsInSlab;
        }

        return total;
    }

    // Add new customer
    void addCustomer() {
        int id, units;
        string name;

        cout << "\n=== Add New Customer ===\n";
        cout << "Enter Customer ID: ";
        cin >> id;
      
        cout << "Enter Customer Name: ";
       cin>>name;

        cout << "Enter Units Consumed: ";
        cin >> units;

        Customer* newCustomer = new Customer(id, name, units);
        newCustomer->billAmount = calculateBill(units);

        newCustomer->next = head;
        head = newCustomer;
        customerCount++;

        cout << "\nCustomer added successfully!\n";
        cout << "Bill Amount: Rs. " << fixed << setprecision(2)
             << newCustomer->billAmount << endl;
    }

    // Display all customers
    void displayAllCustomers() {
        if (head == nullptr) {
            cout << "\nNo customer records found!\n";
            return;
        }

        cout << "\n=== All Customer Records ===\n";
        cout << "-----------------------------------------------------------------\n";
        cout << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(15) << "Units"
             << setw(15) << "Bill(Rs.)\n";
        cout << "-----------------------------------------------------------------\n";

        Customer* current = head;
        while (current != nullptr) {
            cout << setw(10) << current->id
                 << setw(20) << current->name
                 << setw(15) << current->units
                 << setw(15) << fixed << setprecision(2)
                 << current->billAmount << endl;
            current = current->next;
        }

        cout << "-----------------------------------------------------------------\n";
        cout << "Total Customers: " << customerCount << endl;
    }

    // Search customer by ID
    void searchCustomer() {
        if (head == nullptr) {
            cout << "\nNo customer records found!\n";
            return;
        }

        int searchId;
        cout << "\nEnter Customer ID to search: ";
        cin >> searchId;

        Customer* current = head;
        while (current != nullptr) {
            if (current->id == searchId) {
                cout << "\n=== Customer Found ===\n";
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Units Consumed: " << current->units << endl;
                cout << "Bill Amount: Rs. " << fixed
                     << setprecision(2) << current->billAmount << endl;
                return;
            }
            current = current->next;
        }

        cout << "\nCustomer with ID " << searchId << " not found!\n";
    }

    // Display tariff structure
    void displayTariffStructure() {
        cout << "\n=== Electricity Tariff Structure ===\n";
        cout << "-----------------------------------------\n";
        cout << "Slab (Units)\t\tRate (Rs.)\n";
        cout << "-----------------------------------------\n";
        cout << "0 - 100\t\t\t5.0\n";
        cout << "101 - 300\t\t7.0\n";
        cout << "301 - 500\t\t10.0\n";
        cout << "501 - 1000\t\t15.0\n";
        cout << "Above 1000\t\t20.0\n";
        cout << "-----------------------------------------\n";
    }

    // Calculate bill without saving
    void calculateSingleBill() {
        int units;
        cout << "\nEnter units consumed: ";
        cin >> units;

        if (units < 0) {
            cout << "Invalid units!\n";
            return;
        }

        cout << "Total Bill: Rs. "
             << fixed << setprecision(2)
             << calculateBill(units) << endl;
    }

    // Destructor
    ~ElectricityBillSystem() {
        Customer* current = head;
        while (current != nullptr) {
            Customer* next = current->next;
            delete current;
            current = next;
        }
    }
};

// ==================== Main Function ====================
int main() {
    ElectricityBillSystem system;
    int choice;

    do {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Add New Customer\n";
        cout << "2. Display All Customers\n";
        cout << "3. Search Customer by ID\n";
        cout << "4. Calculate Single Bill\n";
        cout << "5. View Tariff Structure\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addCustomer();
                break;
            case 2:
                system.displayAllCustomers();
                break;
            case 3:
                system.searchCustomer();
                break;
            case 4:
                system.calculateSingleBill();
                break;
            case 5:
                system.displayTariffStructure();
                break;
            case 6:
                cout << "\nThank you for using the system!\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
