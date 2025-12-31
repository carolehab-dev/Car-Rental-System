
#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <vector>
#include "Cars.h"
#include "Driver.h"
#include "reservation.h"

// Cars
vector<Cars> loadCars();
void saveCars(const vector<Cars> &cars);

// Reservations
vector<Reservation> loadReservations();
void saveReservations(const vector<Reservation>& reservations);
void saveReservation(const Reservation& r);
void updateReservation(const Reservation &updatedRes);
void saveDrivers(const vector<Driver>& drivers);
vector<Driver> loadDrivers();

#endif
