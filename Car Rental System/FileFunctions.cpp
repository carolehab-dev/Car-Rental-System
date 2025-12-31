#include "FileFunctions.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//================ Cars =================
vector<Cars> loadCars()
{
    vector<Cars> cars;
    ifstream file("cars.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string carId, model, color, carNum, availibility_status, carRentalCost;
        getline(ss, carId, ',');
        getline(ss, model, ',');
        getline(ss, color, ',');
        getline(ss, carNum, ',');
        getline(ss, availibility_status, ',');
        getline(ss, carRentalCost);
        bool available = (availibility_status == "1" || availibility_status == "true");
        cars.push_back(Cars(stoi(carId), model, color, stoi(carNum), available, stod(carRentalCost)));;
    }
    return cars;
}

void saveCars(const vector<Cars> &cars)
{
    ofstream file("cars.csv");
    for (const auto &c : cars)
    {
        file << c.carId << "," << c.model << "," << c.color << ","
             << c.carNum << "," << (c.availibility_status ? "1" : "0") << ","
             << c.carRentalCost << "\n";
    }
}
//================ Reservations =================
vector<Reservation> loadReservations()
{
    vector<Reservation> reservations;
    ifstream file("reservations.txt");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Reservation r;
        string id, custId, carId, days, cost;
        getline(ss, id, ',');
        r.reservationId = stoi(id);
        getline(ss, custId, ',');
        r.customerId = stoi(custId);
        getline(ss, carId, ',');
        r.carId = stoi(carId);
        getline(ss, r.startDate, ',');
        getline(ss, r.endDate, ',');
        getline(ss, days, ',');
        r.totalDays = stoi(days);
        getline(ss, cost, ',');
        r.totalCost = stod(cost);
        getline(ss, r.status);
        reservations.push_back(r);
    }
    return reservations;
}

void saveReservations(const vector<Reservation>& reservations)
{
    ofstream file("reservations.txt"); 

    for (const auto& r : reservations)
    {
        file << r.reservationId << "," << r.customerId << ","
            << r.carId << "," << r.startDate << "," << r.endDate << ","
            << r.totalDays << "," << r.totalCost << "," << r.status << endl;
    }
}
void saveReservation(const Reservation &r) {
    ofstream file("reservations.txt", ios::app);
    file << r.reservationId << "," << r.customerId << ","
        << r.carId << "," << r.startDate << "," << r.endDate
        << "," << r.totalDays << "," << r.totalCost << "," << r.status << endl; 
}
void updateReservation(const Reservation &updatedRes)
{
    vector<Reservation> reservations = loadReservations();
    bool found = false;
    for (auto &r : reservations)
    {
        if (r.reservationId == updatedRes.reservationId)
        {
            r = updatedRes;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Reservation not found!\n";
        return;
    }

    ofstream file("reservations.txt");
    for (auto &r : reservations)
    {
        file << r.reservationId << "," << r.customerId << ","
             << r.carId << "," << r.startDate << "," << r.endDate << ","
             << r.totalDays << "," << r.totalCost << "," << r.status << endl;
    }
}
vector<Driver> loadDrivers() {
    vector<Driver> drivers;
    ifstream file("drivers.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Driver d;
        string id, statusStr;
        getline(ss, id, ',');
        d.id = stoi(id);
        getline(ss, d.uname, ',');
        getline(ss, d.phone, ',');
        getline(ss, statusStr);
        d.status = (statusStr == "1"); // 1 = Available, 0 = Busy
        drivers.push_back(d);
    }
    return drivers;
}

// Saving drivers to file
void saveDrivers(const vector<Driver>& drivers) {
    ofstream file("drivers.txt");
    for (const auto& d : drivers) {
        file << d.id << "," << d.uname << "," << d.phone << "," << (d.status ? "1" : "0") << endl;
    }
}
