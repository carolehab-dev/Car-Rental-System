#pragma once
#include "Cars.h"
#include "Reservation.h"
#include <vector>

class CustomerService {
private:
    Cars allCars;

public:
    int customerId;

    CustomerService();

    void viewAllAvaliableCars();
    int findCarIndexById(const std::vector<Cars>& cars, int id);

    void reserveCar();
    void cancelReservation();
    void viewReservations();
};
