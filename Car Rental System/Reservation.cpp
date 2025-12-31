#include "reservation.h"
#include "FileFunctions.h"
#include <vector>
#include <iostream>
vector<Reservation> Reservation::reserves = loadReservations();

void Reservation::viewMyReservations()
{
    // cout << "\n--- List of Reservations ---\n";
    // for (const auto &r : reserves)
    // {
    //     cout << "ID: " << r.reservationId
    //          << " | Car ID: " << r.carId
    //          << " | Customer ID: " << r.customerId
    //          << " | Start Date: " << r.startDate
    //          << " | End Date: " << r.endDate
    //          << " | Total Days" << r.totalDays
    //          << " | Total Cost: " << r.totalCost
    //          << " | Status: " << r.status
    //          << endl;
    // }
    //reserves = loadReservations();
    bool hasRes = false;
    cout << "\nYour Reservations:\n";
    for (auto& r : reserves)
    {
        if (r.customerId == customerId)
        {
            cout << "ID: " << r.reservationId
                << " | CarID: " << r.carId
                << " | Status: " << r.status
                << " | From: " << r.startDate
                << " To: " << r.endDate
                << " | Cost: " << r.totalCost << endl;
            hasRes = true;
        }
    }
    if (!hasRes)
        cout << "No reservations found.\n";
}

void Reservation::viewAllReservation()
{
    cout << "\n--- List of Reservations ---\n";
    for (const auto& r : reserves)
    {
        cout << "ID: " << r.reservationId
            << " | Car ID: " << r.carId
            << " | Customer ID: " << r.customerId
            << " | Start Date: " << r.startDate
            << " | End Date: " << r.endDate
            << " | Total Days" << r.totalDays
            << " | Total Cost: " << r.totalCost
            << " | Status: " << r.status
            << endl;
    }
}