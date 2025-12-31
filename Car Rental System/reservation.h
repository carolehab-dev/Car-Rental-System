#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
using namespace std;

class Reservation
{
public:
    int reservationId;
    int customerId;
    int carId;
    string startDate;
    string endDate;
    int totalDays;
    double totalCost;
    string status;
    static vector<Reservation> reserves;

    Reservation() {}
    Reservation(int rId, int cId, int car,
        string start, string end,
        int days, double cost) {
        reservationId = rId;
        customerId = cId;
        carId = car;
        startDate = start;
        endDate = end;
        totalDays = days;
        totalCost = cost;
        status = "Active";
    }

    void viewAllReservation();
    void viewMyReservations();
};

#endif