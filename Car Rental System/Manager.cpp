#include "Manager.h"
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;
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
        cout << "\n===== MANAGER MENU =====\n";
        cout << "1. View All Cars\n";
        cout << "2. Add Car\n";
        cout << "3. Update Car\n";
        cout << "4. Delete Car\n";
        cout << "5. View Drivers\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
           // viewAllCars();
            cout << "Logging out...\n";
            break;
        case 2:
           // addCar();
            cout << "Logging out...\n";
            break;
        case 3:
           // updateCar();
            cout << "Logging out...\n";
            break;
        case 4:
           // deleteCar();
            cout << "Logging out...\n";
            break;
        case 5:
           // displayDrivers();
            cout << "Logging out...\n";
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);
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
//void Manager::viewAllCars()
//{
//    carManager.viewAllCars();
//}
//
//// Add Car
//void Manager::addCar()
//{
//    int nextCar = 1;
//    if (!Cars::allCars.empty())
//    {
//        for (const auto &c : Cars::allCars)
//        {
//            if (c.carId >= nextCar)
//                nextCar = c.carId + 1;
//        }
//    }
//
//    Cars newCar;
//    newCar.carId = nextCar;
//    cout << "\n--- Add New Car To The System ---\n";
//    cout << " Model: ";
//    cin >> newCar.model;
//    cout << " Color: ";
//    cin >> newCar.color;
//    cout << " Car Number: ";
//    cin >> newCar.carNum;
//    cout << " Rental Cost: ";
//    cin >> newCar.carRentalCost;
//    cout << " Status: ";
//    cin >> newCar.availibility_status;
//
//    carManager.allCars.push_back(newCar);
//    carManager.appendToFile("cars.csv", newCar);
//}
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