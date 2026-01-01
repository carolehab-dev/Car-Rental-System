#pragma once
#include "User.h"
#include "Cars.h"
//#include "Driver.h"
#include <vector>
#include <string>
using namespace std;
class Manager : public User
{
private:
    Cars carManager;

public:
 //   vector<Driver> drivers;
    Manager(int id, const string& uname);
    bool login() override;
    void showMenu() override;
    //Manager();
    void readDataFromFile(const string &filename);
    void viewDrivers();
    void addDriver();
    void updateDriver();
    void deleteDriver();

    void viewAllCars();
    void addCar();
    void updateCar();
    void deleteCar();
};


