//#include "reservation.h"
//#include "FileFunctions.h"
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//vector<Reservation> Reservation::reserves = loadReservations();
//
//void Reservation::viewMyReservations()
//{
//    // cout << "\n--- List of Reservations ---\n";
//    // for (const auto &r : reserves)
//    // {
//    //     cout << "ID: " << r.reservationId
//    //          << " | Car ID: " << r.carId
//    //          << " | Customer ID: " << r.customerId
//    //          << " | Start Date: " << r.startDate
//    //          << " | End Date: " << r.endDate
//    //          << " | Total Days" << r.totalDays
//    //          << " | Total Cost: " << r.totalCost
//    //          << " | Status: " << r.status
//    //          << endl;
//    // }
//    //reserves = loadReservations();
//    bool hasRes = false;
//    cout << "\nYour Reservations:\n";
//    for (auto& r : reserves)
//    {
//        if (r.customerId == customerId)
//        {
//            cout << "ID: " << r.reservationId
//                << " | CarID: " << r.carId
//                << " | Status: " << r.status
//                << " | From: " << r.startDate
//                << " To: " << r.endDate
//                << " | Cost: " << r.totalCost << endl;
//            hasRes = true;
//        }
//    }
//    if (!hasRes)
//        cout << "No reservations found.\n";
//}
//
//void Reservation::viewAllReservation()
//{
//    cout << "\n--- List of Reservations ---\n";
//    for (const auto& r : reserves)
//    {
//        cout << "ID: " << r.reservationId
//            << " | Car ID: " << r.carId
//            << " | Customer ID: " << r.customerId
//            << " | Start Date: " << r.startDate
//            << " | End Date: " << r.endDate
//            << " | Total Days" << r.totalDays
//            << " | Total Cost: " << r.totalCost
//            << " | Status: " << r.status
//            << endl;
//    }
//}

#include "Reservation.h"
#include "FileFunctions.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ===== Static member definition =====
vector<Reservation> Reservation::reserves;

// ===== Constructors =====
Reservation::Reservation() {}

Reservation::Reservation(int custId,
    int cId,
    const string& start,
    const string& end,
    int days,
    double cost,
    int dId)
{
    reservationId = getNextReservationId();
    customerId = custId;
    carId = cId;
    startDate = start;
    endDate = end;
    totalDays = days;
    totalCost = cost;
    status = "Active";
    driverId = dId;
}

// ===== Load from file =====
void Reservation::loadFromFile()
{
    reserves = ::loadReservations(); // global function from FileFunctions
}

// ===== Generate next ID =====
int Reservation::getNextReservationId()
{
    ifstream file("reservations.txt");
    string line, lastLine;

    while (getline(file, line))
        if (!line.empty())
            lastLine = line;

    if (lastLine.empty())
        return 1;

    stringstream ss(lastLine);
    string idStr;
    getline(ss, idStr, ',');
    return stoi(idStr) + 1;
}

void Reservation::viewMyReservations(int custId)
{
    bool found = false;
    cout << "\n--- Your Reservations ---\n";

    for (const auto& r : reserves)
    {
        if (r.customerId == custId)
        {
            cout << "ID: " << r.reservationId
                << " | CarID: " << r.carId
                << " | From: " << r.startDate
                << " To: " << r.endDate
                << " | Cost: " << r.totalCost
                << " | Status: " << r.status;

            if (r.driverId != -1)
                cout << " | DriverID: " << r.driverId;

            cout << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No reservations found.\n";
}

void Reservation::viewAllReservation()
{
    cout << "\n--- All Reservations ---\n";

    for (const auto& r : reserves)
    {
        cout << "ID: " << r.reservationId
            << " | CustomerID: " << r.customerId
            << " | CarID: " << r.carId
            << " | From: " << r.startDate
            << " To: " << r.endDate
            << " | Cost: " << r.totalCost
            << " | Status: " << r.status
            << endl;
    }
}