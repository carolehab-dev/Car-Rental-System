#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

    class Reservation
    {
    public:
        int reservationId;
        int customerId;
        int carId;
        std::string startDate;
        std::string endDate;
        int totalDays;
        double totalCost;
        std::string status;
        int driverId; 
        Reservation() {
        }
        Reservation(int resId, int custId, int cId, std::string start, std::string end, int days, double cost, int dId = -1)
            : reservationId(resId), customerId(custId), carId(cId), startDate(start), endDate(end), totalDays(days), totalCost(cost), status("Active"), driverId(dId) {
            reservationId = getNextReservationId();
        }
        int getNextReservationId()
        {
            ifstream file("reservations.txt");
            string line, lastLine;

            while (getline(file, line))
                if (!line.empty()) lastLine = line;

            if (lastLine.empty()) return 1;

            stringstream ss(lastLine);
            string idStr;
            getline(ss, idStr, ','); 
            return stoi(idStr) + 1;
        }
    };



#endif
