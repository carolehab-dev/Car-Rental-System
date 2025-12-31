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
static vector<string> managerMenuOptions = {
    "View All Cars",
    "View All Reservations",
    "View All Feedbacks",
    "Add Car",
    "Update Car",
    "Delete Car",
    "View Drivers",
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
            Reservation r;
            r.viewAllReservation();
            pauseScreen();
            break;
        }

        case 2: { 
           /* Feedback f;
            f.viewAllFeedbacks();
            pauseScreen();*/
            cout << "Logging out...\n";
            break;
        }

        case 3: // Add Car
            addCar();
            pauseScreen();
            break;

        case 4: // Update Car
          /*  updateCar();
            pauseScreen();*/
            cout << "Logging out...\n";
            break;

        case 5: // Delete Car
           /* deleteCar();
            pauseScreen();*/
            cout << "Logging out...\n";
            break;

        case 6: // View Drivers
            // displayDrivers();
            cout << "\n[Driver management not implemented yet]\n";
            pauseScreen();
            break;

        case 7: // Logout
            cout << "Logging out...\n";
            break;
        }
    } while (choice != 7);
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
//
//// Upadte A Car
//void Manager::updateCar()
//{
//    int toBeUpadtedId = 0;
//    int newRentalCost = 0;
//    cout << "\n--- Specify The Car ID You Want To Update ---\n";
//    cout << "Enter ID: ";
//    cin >> toBeUpadtedId;
//    bool found = false;
//    for (auto &c : Cars::allCars)
//    {
//        if (c.carId == toBeUpadtedId)
//        {
//            cout << "Specify The Car New Rental Cost: ";
//            cin >> newRentalCost;
//            c.carRentalCost = newRentalCost;
//            found = true;
//        }
//    }
//    if (!found)
//    {
//        cout << "No Car Found With This ID \n";
//    }
//    carManager.saveToFile("cars.csv", Cars::allCars);
//}
//
//// delete A Car
//void Manager::deleteCar()
//{
//    int toBeDeletedId = 0;
//    cout << "\n--- Specify The Car ID You Want To Delete ---\n";
//    cout << "Enter ID: ";
//    cin >> toBeDeletedId;
//    bool found = false;
//    auto itr = Cars::allCars.begin();
//    while (itr != Cars::allCars.end())
//    {
//        if (itr->carId == toBeDeletedId)
//        {
//            itr = Cars::allCars.erase(itr);
//            found = true;
//        }
//        else
//        {
//            itr++;
//        }
//    }
//    if (!found)
//    {
//        cout << "No Car Found With This ID \n";
//    }
//    carManager.saveToFile("cars.csv", Cars::allCars);
//}