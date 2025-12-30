//#pragma once
//#include "User.h"
//class Customer :public User
//{
//public:
//    Customer(int userId,
//        const string& username,
//        const string& fullName,
//        const string& phone,
//        const string& nationalId);
//    bool login() override;
//    void showMenu() override;
//    static bool Register();
//    //void loadProfile();
//    int getCustomerId() const;
//    string getFullName() const;
//    string getPhone() const;
//    string getNationalId() const;
//private:
//    int customerId{};
//    string fullName;
//    string phone;
//    string nationalId;
//};
#pragma once
#include "User.h"
#include "Cars.h"
#include "Reservation.h"
#include <vector>
#include <string>
using namespace std;
class Customer : public User
{
public:
 
    Customer(int userId,
        const string& username,
        const string& fullName,
        const string& phone,
        const string& nationalId);

    bool login() override;
    void showMenu() override;
    static bool Register();
    void viewAllAvaliableCars();
    void reserveCar();
    void cancelReservation();
    void viewReservations();
    int getCustomerId() const;
    string getFullName() const;
    string getPhone() const;
    string getNationalId() const;

private:
    int customerId;
    string fullName;
    string phone;
    string nationalId;
    int findCarIndexById(const vector<Cars>& cars, int id);
};