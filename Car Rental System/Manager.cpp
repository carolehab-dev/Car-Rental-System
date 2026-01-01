#include "Manager.h"
#include <fstream>
#include <sstream>
#include <iostream>       
#include "Cars.h"            
#include "reservation.h"     
#include "Feedbacks.h"
#include "File.h"             
#include "FileFunctions.h" 
#include <conio.h>
#include "Customer.h"
using namespace std;
int showVerticalMenu(
    const string& title,
    const vector<string>& options
)
{
    int selected = 0;

    while (true)
    {
        system("cls");

        cout << "\n===== " << title << " =====\n\n";

        for (int i = 0; i < options.size(); i++)
        {
            if (i == selected)
                cout << " > " << options[i] << endl;
            else
                cout << "   " << options[i] << endl;
        }

        char key = _getch();

        if (key == 72 && selected > 0)              // UP arrow
            selected--;
        else if (key == 80 && selected < options.size() - 1) // DOWN arrow
            selected++;
        else if (key == 13)                         // ENTER
            return selected;
    }
}
void pauseScreen()
{
    cout << "\nPress any key to continue...";
    _getch();
}

static int getNextDriverId(const string& filename)
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
static vector<string> managerMenuOptions = {
     "View All Cars",
    "View All Reservations",
    "View All Feedbacks",
    "Add Car",
    "Update Car",
    "Delete Car",
    "View Drivers",
    "Add Driver",
    "Update Driver",
    "Delete Driver",
    "Logout"
};
//Manager::Manager() : User(), carManager() {};
Manager::Manager(int id, const string& uname)
{
    user_Id = id;
    userName = uname;
    role = Role_Manager;
}
bool Manager::login()
{
    cout << "\nWelcome Manager " << userName << " \n";
    return true;
}
void Manager::showMenu()
{
    int choice;
    do {
        choice = showVerticalMenu(
            "MANAGER MENU",
            managerMenuOptions
        );

        switch (choice)
        {
        case 0: 
            viewAllCars();
            pauseScreen();
            break;

        case 1: { 
            /*Reservation r;
            r.viewAllReservation();*/
            Reservation::loadFromFile();     
            Reservation::viewAllReservation();
            pauseScreen();
            break;
        }

        case 2: { 
            Feedback f;
            f.viewAllFeedbacks();
            pauseScreen();
            break;
        }

        case 3: // Add Car
            addCar();
            pauseScreen();
            break;

        case 4: // Update Car
            updateCar();
            pauseScreen();
            cout << "Logging out...\n";
            break;

        case 5: // Delete Car
            deleteCar();
            pauseScreen();
            cout << "Logging out...\n";
            break;

        case 6:
            viewDrivers();
            pauseScreen();
            break;

        case 7:
            addDriver();
            pauseScreen();
            break;

        case 8:
            updateDriver();
            pauseScreen();
            break;

        case 9:
            deleteDriver();
            pauseScreen();
            break;

        case 10:
            cout << "Logging out...\n";
            break;
        }
    } while (choice != 10);
}

//// Read data from CSV file
//void Manager::readDataFromFile(const string &filename)
//{
//    ifstream file(filename);
//    string line;
//
//    getline(file, line); // skip header
//
//    while (getline(file, line))
//    {
//        stringstream ss(line);
//        string id, uname, pass, phone, r, nid;
//
//        getline(ss, id, ',');
//        getline(ss, uname, ',');
//        getline(ss, pass, ',');
//        getline(ss, phone, ',');
//        getline(ss, r, ',');
//        getline(ss, nid, ',');
//
//        if (r == "driver")
//        {
//            drivers.push_back(
//                Driver(stoi(id), uname, pass, phone, r, nid, true));
//        }
//    }
//}
//
//// Add driver
//void Manager::addDriver(Driver d)
//{
//    drivers.push_back(d);
//    cout << "Driver added: " << d.getUsername() << endl;
//}
//
//// Update driver
//void Manager::updateDriver(int driverId, string newPhone)
//{
//    for (auto &d : drivers)
//    {
//        if (d.getUserId() == driverId)
//        {
//            d.setPhoneNumber(newPhone);
//            cout << "Driver updated: " << d.getUsername() << endl;
//            return;
//        }
//    }
//    cout << "Driver not found!" << endl;
//}
//
//// Delete driver
//void Manager::deleteDriver(int driverId)
//{
//    for (auto it = drivers.begin(); it != drivers.end(); ++it)
//    {
//        if (it->getUserId() == driverId)
//        {
//            cout << "Driver deleted: " << it->getUsername() << endl;
//            drivers.erase(it);
//            return;
//        }
//    }
//    cout << "Driver not found!" << endl;
//}
//
//// Display drivers
//void Manager::displayDrivers()
//{
//    for (auto &d : drivers)
//    {
//        cout << d.getUserId() << " "
//             << d.getUsername() << " "
//             << endl;
//    }
//}
//
// 
// 
void Manager::viewDrivers()
{
    vector<Driver> drivers = loadDrivers();

    if (drivers.empty())
    {
        cout << "No drivers found.\n";
        return;
    }

    cout << "\n--- Drivers List ---\n";
    for (const auto& d : drivers)
    {
        cout << "DriverID: " << d.id
            << " | UserID: " << d.getUserId()
            << " | Username: " << d.uname
            << " | Phone: " << d.phone
            << " | NationalID: " << d.nid
            << " | Status: " << (d.status ? "Available" : "Busy")
            << endl;
    }
}
void Manager::addDriver()
{
    string username, password, phone, nid;

    cout << "\n--- Add New Driver ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << "Phone: ";
    cin >> phone;
    cout << "National ID: ";
    cin >> nid;

    int userId = getNextDriverId("users.txt");
    int driverId =getNextDriverId("drivers.txt");

    // users.txt
    ofstream users("users.txt", ios::app);
    users << userId << "," << username << "," << password << "," << Role_Driver << "\n";
    users.close();

    // drivers.txt
    ofstream drivers("drivers.txt", ios::app);
    drivers << driverId << "," << userId << "," << username << ","
        << phone << "," << nid << ",1\n"; // available
    drivers.close();

    cout << "Driver added successfully.\n";
}
void Manager::updateDriver()
{
    viewDrivers();
    vector<Driver> drivers = loadDrivers();
    int driverId;
    cout << "Enter Driver ID to update: ";
    cin >> driverId;

    bool found = false;
    for (auto& d : drivers)
    {
        if (d.id == driverId)
        {
            cout << "New Phone: ";
            cin >> d.phone;
            cout << "Status (1 = Available, 0 = Busy): ";
            cin >> d.status;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Driver not found.\n";
        return;
    }

    saveDrivers(drivers);
    cout << "Driver updated successfully.\n";
}
void Manager::deleteDriver()
{
    viewDrivers();
    vector<Driver> drivers = loadDrivers();

    int driverId;
    cout << "Enter Driver ID to delete: ";
    cin >> driverId;

    bool found = false;
    auto it = drivers.begin();

    while (it != drivers.end())
    {
        if (it->id == driverId)
        {
            it = drivers.erase(it);
            found = true;
            break;
        }
        else
            ++it;
    }

    if (!found)
    {
        cout << "Driver not found.\n";
        return;
    }

    saveDrivers(drivers);
    cout << "Driver deleted successfully.\n";
}

//// Diplay Cars
void Manager::viewAllCars()
{
    File<Cars> file;
    Cars::allCars.clear();
    file.readFromFile("cars.csv", Cars::allCars);
    Cars temp;
    temp.viewAllCars();
}

void Manager::addCar()
{
    File<Cars> file;
    Cars::allCars.clear();
    file.readFromFile("cars.csv", Cars::allCars);

    int nextCarId = 1;
    for (const auto& c : Cars::allCars)
    {
        if (c.carId >= nextCarId)
            nextCarId = c.carId + 1;
    }

    Cars newCar;
    newCar.carId = nextCarId;

    cout << "\n--- Add New Car ---\n";
    cout << "Model: ";
    cin >> newCar.model;
    cout << "Color: ";
    cin >> newCar.color;
    cout << "Car Number: ";
    cin >> newCar.carNum;
    cout << "Rental Cost: ";
    cin >> newCar.carRentalCost;
    cout << "Availability (1 = Available, 0 = Not Available): ";
    cin >> newCar.availibility_status;

    Cars::allCars.push_back(newCar);
    saveCars(Cars::allCars);

    cout << "Car added successfully.\n";
}

// Upadte A Car
void Manager::updateCar()
{
    viewAllCars();
    File<Cars> file;
    Cars::allCars.clear();
    file.readFromFile("cars.csv", Cars::allCars);
    int toBeUpadtedId = 0;
    int newRentalCost = 0;
    cout << "\n--- Specify The Car ID You Want To Update ---\n";
    cout << "Enter ID: ";
    cin >> toBeUpadtedId;
    bool found = false;
    for (auto &c : Cars::allCars)
    {
        if (c.carId == toBeUpadtedId)
        {
            cout << "Specify The Car New Rental Cost: ";
            cin >> newRentalCost;
            c.carRentalCost = newRentalCost;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Car Found With This ID \n";
    }
    //carManager.saveToFile("cars.csv", Cars::allCars);
    saveCars(Cars::allCars);
}

// delete A Car
void Manager::deleteCar()
{
    viewAllCars();
    File<Cars> file;
    Cars::allCars.clear();
    file.readFromFile("cars.csv", Cars::allCars);
    int toBeDeletedId = 0;
    cout << "\n--- Specify The Car ID You Want To Delete ---\n";
    cout << "Enter ID: ";
    cin >> toBeDeletedId;
    bool found = false;
    auto itr = Cars::allCars.begin();
    while (itr != Cars::allCars.end())
    {
        if (itr->carId == toBeDeletedId)
        {
            itr = Cars::allCars.erase(itr);
            found = true;
        }
        else
        {
            itr++;
        }
    }
    if (!found)
    {
        cout << "No Car Found With This ID \n";
    }
   // carManager.saveToFile("cars.csv", Cars::allCars);
    saveCars(Cars::allCars);
}