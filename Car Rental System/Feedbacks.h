#ifndef FEEDBACKS_H
#define FEEDBACKS_H

#include <string>
#include <vector>
#include <string>

// #include "Cars.h"

using namespace std;

class Feedback
{

public:
    int feedbackId;
    int reservationId;
    int carId;
    int customerId;
    int rating;
    string comment;
    static vector<Feedback> feedbacks;

    void createFeedback(int resId, int custId, int carId);
    void viewAllFeedbacks();

};

void loadFeedbacks(vector<Feedback>& feedbacks, const string& filename = "feedbacks.csv");
void appendFeedback(const Feedback& fb, const string& filename = "feedbacks.csv");
#endif