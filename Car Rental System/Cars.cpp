#include <iostream>
#include <fstream>
#include <sstream>
#include "Cars.h"
#include "File.h"
#include "FileFunctions.h"
#include "HelperFunction.h"

vector<Cars> Cars::allCars;

Cars::Cars(){}

void Cars::viewAllCars()
{
    cout << "\n--- List of Cars ---\n";
    for (const auto &c : allCars)
    {
        cout << "ID: " << c.carId
             << " | Model: " << c.model
             << " | Color: " << c.color
             << " | Car Number: " << c.carNum
             << " | Rental Cost: " << c.carRentalCost
             << " | Status: " << (c.availibility_status == 1 ? "is Available" : "Not Available")
             << endl;
    }
}

void Cars::viewCarInfo(int id)
{
    cout << "\n--- List of Car Information ---\n";
    if (!allCars.empty())
    {
        for (auto itr = allCars.begin(); itr != allCars.end(); itr++)
        {
            if (itr->carId == id)
            {
                cout << "ID: " << itr->carId
                     << " | Model: " << itr->model
                     << " | Color: " << itr->color
                     << " | Car Number: " << itr->carNum
                     << " | Rental Cost: " << itr->carRentalCost
                     << " | Status: " << (itr->availibility_status == 1 ? "is Available" : "Not Available")
                     << endl;
            }
        }
    }
    cout << "No Car Available with this ID.. \n";
}

void Cars::viewAllAvaliableCars()
{
    allCars.clear(); // added carol
    readFromFile("cars.csv", allCars); //  added carol
    cout << "\n--- List of All Availiable Cars ---\n";
    for (const auto &c : allCars)
    {
        if (c.availibility_status == 0)
        {
            cout << "ID: " << c.carId
                 << " | Model: " << c.model
                 << " | Color: " << c.color
                 << " | Car Number: " << c.carNum
                 << " | Rental Cost: " << c.carRentalCost
                 << " | Status: " << (c.availibility_status == 0 ? "is Available" : "Not Available")
                 << endl;
        }
    }

}


void Cars::updateCarsStatus()
{
    vector<Cars> cars = loadCars();
    vector<Reservation> reservations = loadReservations();

    for (auto& r : reservations)
    {
        if (r.status == "Active" && HelperFunctions::isEndDateFinished(r.endDate))
        {
            
            r.status = "Finished";

            
            for (auto& car : cars)
            {
                if (car.carId == r.carId)
                {
                    car.availibility_status = 0; 
                    break;
                }
            }
        }
    }

    saveCars(cars);
    saveReservations(reservations);
}


