
#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <vector>
#include "Cars.h"
#include "reservation.h"

// Cars
vector<Cars> loadCars();
void saveCars(const vector<Cars> &cars);

// Reservations
vector<Reservation> loadReservations();
void saveReservation(const Reservation &r);
void updateReservation(const Reservation &updatedRes);

#endif
