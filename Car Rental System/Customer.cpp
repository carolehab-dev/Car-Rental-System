#include "Customer.h"
#include "FileFunctions.h"
#include "HelperFunction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Feedbacks.h"

using namespace std;

static bool usernameExists(const string& username)
{
    fstream file("users.txt", ios::in);
    string line, id, u;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, u, ',');
        if (u == username) return true;
    }
    return false;
}

static int getNextId(const string& filename)
{
    fstream file(filename, ios::in);
    string line, lastLine;

    while (getline(file, line))
        if (!line.empty()) lastLine = line;

    if (lastLine.empty()) return 1;

    string idStr;
    stringstream ss(lastLine);
    getline(ss, idStr, ',');
    return stoi(idStr) + 1;
}

Customer::Customer(int userId,
    const string& username,
    const string& name,
    const string& phone,
    const string& nid)
{
    user_Id = userId;
    userName = username;
    fullName = name;
    this->phone = phone;
    nationalId = nid;
    customerId = userId;
    role = Role_Customer;
}

bool Customer::login()
{
    cout << "Welcome, " << fullName << " \n";
    return true;
}

void Customer::showMenu()
{
    int choice;
    do {
        cout << "\n===== CUSTOMER MENU =====\n";
        cout << "1. View Available Cars\n";
        cout << "2. Reserve Car\n";
        cout << "3. View Reservations\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Add Feedback\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllAvaliableCars();
            break;
        case 2:
            reserveCar();
            break;
        case 3:
            viewReservations();
            break;
        case 4:
            cancelReservation();
            break;
        case 5:
            createFeedback();
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);
}


void Customer::viewAllAvaliableCars()
{
    Cars::allCars.clear();
    Cars temp;
    temp.readFromFile("cars.csv", Cars::allCars);
    temp.viewAllAvaliableCars();
}

int Customer::findCarIndexById(const vector<Cars>& cars, int id)
{
    for (int i = 0; i < cars.size(); i++)
        if (cars[i].carId == id && cars[i].isAvailable())
            return i;
    return -1;
}

void Customer::reserveCar()
{
    //static int nextReservationId = 1;
    bool isValid;
    string start, end;
    int  days;
    vector<Cars> cars = loadCars();
    vector<Driver> drivers = loadDrivers(); 

    cout << "Available Cars:\n";
    viewAllAvaliableCars();

    int chosenId;
    cout << "\nEnter Car ID to reserve: ";
    cin >> chosenId;

    int index = -1;
    for (int i = 0; i < cars.size(); i++)
        if (cars[i].carId == chosenId)
            index = i;

    if (index == -1 || cars[index].isAvailable())
    {
        cout << "Car not available!\n";
        return;
    }
    do 
    {
        cout << "Start Date (dd-mm-yyyy): ";
        cin >> start;
        cout << "End Date (dd-mm-yyyy): ";
        cin >> end;
        isValid=HelperFunctions::validateStartEndDates(start, end);
        days = HelperFunctions::calculateDays(start, end);
    } while(!isValid);

    double cost = days * cars[index].carRentalCost;

    int driverId = -1; 
    char wantDriver;
    cout << "Do you want a driver? (y/n): ";
    cin >> wantDriver;

    if (wantDriver == 'y' || wantDriver == 'Y')
    {
        bool assigned = false;
        for (auto& d : drivers)
        {
            if (!d.status) 
            {
                driverId = d.id;
                d.status = 1; 
                assigned = true;
                break;
            }
        }
        if (!assigned)
        {
            cout << "No drivers available. You can continue without a driver (c) or cancel reservation (x): ";
            char choice;
            cin >> choice;
            if (choice == 'x' || choice == 'X') return; // ????? ?????
        }
    }

    
    Reservation r(
        customerId,
        cars[index].carId,
        start,
        end,
        days,
        cost,
        driverId
    );
    cars[index].reserve(); 
    saveCars(cars);
    saveReservation(r);
    saveDrivers(drivers); 

    cout << "\nReservation Successful!\n";
    cout << "Total Cost: " << r.totalCost << endl;
    if (driverId != -1)
        cout << "Driver assigned: " << driverId << endl;
}


void Customer::cancelReservation()
{
    vector<Reservation> reservations = loadReservations();
    vector<Cars> cars = loadCars();

    int resId;
    cout << "Enter Reservation ID to cancel: ";
    cin >> resId;

    for (auto& r : reservations)
    {
        if (r.reservationId == resId &&
            r.customerId == customerId &&
            r.status == "Active")
        {
            r.status = "Canceled";

            for (auto& c : cars)
                if (c.carId == r.carId)
                    c.makeAvailable();

            saveReservations(reservations);
            saveCars(cars);

            cout << "Reservation canceled successfully\n";
            return;
        }
    }
    cout << "Reservation not found\n";
}

void Customer::viewReservations()
{
    vector<Reservation> reservations = loadReservations();
    bool found = false;

    cout << "\nYour Reservations:\n";
    for (auto& r : reservations)
    {
        if (r.customerId == customerId)
        {
            cout << "ID: " << r.reservationId
                << " | CarID: " << r.carId
                << " | Status: " << r.status
                << " | From: " << r.startDate << " To: " << r.endDate
                << " | Cost: " << r.totalCost;

            if (r.driverId != -1)
                cout << " | DriverID: " << r.driverId;

            cout << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No reservations found.\n";
}

int Customer::getCustomerId() const { return customerId; }
string Customer::getFullName() const { return fullName; }
string Customer::getPhone() const { return phone; }
string Customer::getNationalId() const { return nationalId; }

bool Customer::Register() {
    string fullName, username, password, phone, nationalId;
    cout << "Full Name: ";
    //cin.ignore();
    getline(cin, fullName);
    cout << "Username: ";
    cin >> username;
    if (usernameExists(username)) {
        cout << "Username already exists";
        return false;
    }
    cout << "Password: ";
    cin >> password;
    cout << "Phone Number: ";
    cin >> phone;
    cout << "National ID: ";
    cin >> nationalId;
    int userId = getNextId("users.txt");
    int customerId = getNextId("customers.txt");
    fstream users("users.txt", ios::out | ios::app);
    users << userId << "," << username << "," << password << ",0\n";
    users.close();
    fstream customers("customers.txt", ios::out | ios::app);
    customers << customerId << "," << userId << "," << fullName << "," << phone << "," << nationalId << "\n";
    customers.close();
    cout << "Customer registered successfully \n";
    return true;
}
void Customer::createFeedback()
{
    vector<Reservation> reservations = loadReservations();
    bool found = false;

    cout << "\n--- Your Completed Reservations ---\n";

    for (const auto& r : reservations)
    {
        if (r.customerId == customerId && r.status == "Active")
        {
            cout << "Reservation ID: " << r.reservationId
                << " | Car ID: " << r.carId
                << " | From: " << r.startDate
                << " To: " << r.endDate << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No reservations available for feedback.\n";
        return;
    }
    int resId;
    cout << "\nEnter Reservation ID to give feedback: ";
    cin >> resId;

    for (const auto& r : reservations)
    {
        if (r.reservationId == resId &&
            r.customerId == customerId &&
            r.status == "Active")
        {
            Feedback fed;
            fed.createFeedback(
                r.reservationId,
                customerId,
                r.carId
            );
            return;
        }
    }

    cout << "Invalid reservation ID.\n";
}
