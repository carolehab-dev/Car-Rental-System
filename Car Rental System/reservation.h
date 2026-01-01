//#ifndef RESERVATION_H
//#define RESERVATION_H
//
//#include <string>
//#include <fstream>
//#include <sstream>
//using namespace std;
//
//    class Reservation
//    {
//    public:
//        int reservationId;
//        int customerId;
//        int carId;
//        std::string startDate;
//        std::string endDate;
//        int totalDays;
//        double totalCost;
//        std::string status;
//        int driverId; 
//        Reservation() {
//        }
//        Reservation(int resId, int custId, int cId, std::string start, std::string end, int days, double cost, int dId = -1)
//            : reservationId(resId), customerId(custId), carId(cId), startDate(start), endDate(end), totalDays(days), totalCost(cost), status("Active"), driverId(dId) {
//            reservationId = getNextReservationId();
//        }
//        int getNextReservationId()
//        {
//            ifstream file("reservations.txt");
//            string line, lastLine;
//
//            while (getline(file, line))
//                if (!line.empty()) lastLine = line;
//
//            if (lastLine.empty()) return 1;
//
//            stringstream ss(lastLine);
//            string idStr;
//            getline(ss, idStr, ','); 
//            return stoi(idStr) + 1;
//        }
//    };
//
//
////#include <string>
////#include <vector>
////
////class Reservation
////{
////public:
////    int reservationId;
////    int customerId;
////    int carId;
////    std::string startDate;
////    std::string endDate;
////    int totalDays;
////    double totalCost;
////    std::string status;
////    int driverId;
////    static std::vector<Reservation> reserves;
////    Reservation();
////    /*Reservation(int custId,
////        int carId,
////        const std::string& start,
////        const std::string& end,
////        int days,
////        double cost,
////        int driverId = -1);*/
////    Reservation(int resId, int custId, int cId, std::string start, std::string end, int days, double cost, int dId = -1)
////        /          : reservationId(resId), customerId(custId), carId(cId), startDate(start), endDate(end), totalDays(days), totalCost(cost), status("Active"), driverId(dId) {
////                    reservationId = getNextReservationId();
////               }
////
////    static void loadFromFile();
////    static void viewAllReservation();
////    static void viewMyReservations(int customerId);
////
////private:
////    static int getNextReservationId();
////};
////
//#endif

#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>

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

    // ===== Static storage =====
    static std::vector<Reservation> reserves;

    // ===== Constructors =====
    Reservation();
    Reservation(int custId,
        int carId,
        const std::string& start,
        const std::string& end,
        int days,
        double cost,
        int driverId = -1);

    // ===== Views =====
    static void loadFromFile();
    static void viewAllReservation();
    static void viewMyReservations(int customerId);

private:
    static int getNextReservationId();
};

#endif
