#include "Driver.h"
#include <iostream>
#include <fstream>

using namespace std;

Driver::Driver()
{
    status = true;
}

Driver::Driver(int driverId,
    int userId,
    const string& username,
    const string& phone,
    const string& roleStr,
    const string& nid,
    bool s)
{
    id = driverId;           
    user_Id = userId;        
    userName = username;
    uname = username;
    this->phone = phone;
    r = roleStr;
    this->nid = nid;
    status = s;
    role = Role_Driver;
}

bool Driver::login()
{
    cout << "\nWelcome Driver " << uname << endl;
    return true;
}

void Driver::showMenu()
{
    int choice;
    do {
        cout << "\n===== DRIVER MENU =====\n";
        cout << "1. View My Shifts\n";
        cout << "2. Report Issue\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewMyShifts();
            break;
        case 2:
            reportIssue();
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);
}

// View reservations assigned to THIS DRIVER ID
void Driver::viewMyShifts()
{
    Reservation::loadFromFile();

    bool found = false;
    cout << "\n--- My Assigned Shifts ---\n";

    for (const auto& rsv : Reservation::reserves)
    {
        if (rsv.driverId == id) 
        {
            cout << "Reservation ID: " << rsv.reservationId
                << " | Car ID: " << rsv.carId
                << " | From: " << rsv.startDate
                << " To: " << rsv.endDate
                << " | Status: " << rsv.status
                << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No assigned shifts.\n";
}

void Driver::reportIssue()
{
    cin.ignore();
    string issue;

    cout << "\nDescribe the issue: ";
    getline(cin, issue);

    ofstream file("driver_issues.txt", ios::app);
    file << id << "," << issue << endl;  
    file.close();

    cout << "Issue reported successfully.\n";
}