#ifndef CARS_H
#define CARS_H
#include <iostream>
#include <vector>
#include "File.h"
using namespace std;

class Cars  : public File<Cars>
{

public:
    int carId;
    string model;
    string color;
    int carNum;
    bool availibility_status;
    double carRentalCost;
    static vector<Cars> allCars;

    Cars();
    Cars(int _carId, string _model, string _color, int _carNum, bool _availibility_status, double _carRentalCost)
    {
        carId = _carId;
        model = _model;
        color = _color;
        carNum = _carNum;
        availibility_status = _availibility_status;
        carRentalCost = _carRentalCost;
    }

    void viewAllCars();
    void viewAllAvaliableCars();
    void viewCarInfo(int id);

    void reserve() { availibility_status = 1; }
    void makeAvailable() { availibility_status = 0; }
    bool isAvailable() const { return availibility_status; }
   static void  updateCarsStatus();
};

#endif
