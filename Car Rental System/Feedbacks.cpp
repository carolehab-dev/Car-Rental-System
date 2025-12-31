#include "Feedbacks.h"
#include "File.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>

vector<Feedback> Feedback::feedbacks;

void loadFeedbacks(vector<Feedback>& feedbacks, const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Note: '" << filename << "' not found. Starting with empty feedback list.\n";
        return;
    }

    string line;
    if (!getline(file, line))
        return;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string token;
        vector<string> fields;

        while (getline(ss, token, ','))
        {

            if (!token.empty() && token.front() == '"' && token.back() == '"')
            {
                token = token.substr(1, token.size() - 2);
            }
            fields.push_back(token);
        }

        if (fields.size() < 6)
            continue;

        Feedback fb;
        fb.feedbackId = stoi(fields[0]);
        fb.reservationId = stoi(fields[1]);
        fb.customerId = stoi(fields[2]);
        fb.carId = stoi(fields[3]);
        fb.rating = stoi(fields[4]);
        fb.comment = fields[5];

        feedbacks.push_back(fb);
    }

    file.close();
}
void appendFeedback(const Feedback& fb, const string& filename)
{
    fstream file(filename, ios::in | ios::out | ios::app);
    if (!file.is_open())
    {
        cout << "Error opening " << filename << endl;
        return;
    }

    file.seekp(0, ios::end);
    if (file.tellp() == 0)
    {
        file << "feedBackId,reservationId,customerId,carId,rating,comment\n";
    }
    else
    {
        file.seekg(-1, ios::end);
        char ch;
        file.get(ch);
        file.seekp(0, ios::end);
        if (ch != '\n' && ch != '\r')
            file << "\n";
    }

    file << fb.feedbackId << ","
        << fb.reservationId << ","
        << fb.customerId << ","
        << fb.carId << ","
        << fb.rating << ",\""
        << fb.comment << "\"\n";

    file.close();
    cout << "Feedback recorded successfully.\n";
}

void Feedback::createFeedback(int resId, int custId, int carId)
{
    int index = 1;
    if (!Feedback::feedbacks.empty())
    {
        for (const auto& f : Feedback::feedbacks)
        {
            if (f.feedbackId >= index)
            {
                // cout<< f.feedbackId << "\n";
                index = f.feedbackId + 1;
            }
        }
    }
    Feedback feed;
    feed.feedbackId = index;
    feed.reservationId = resId;
    feed.customerId = custId;
    feed.carId = carId;

    cout << "\n--- Add Your Feedback ---\n";
    cout << " Rating: ";
    cin >> feed.rating;
    cout << " Comment: ";
    cin >> feed.comment;

    Feedback::feedbacks.push_back(feed);
    appendFeedback(feed);
};

void Feedback::viewAllFeedbacks()
{
    cout << "\n--- List of FeedBacks ---\n";
    for (const auto& f : feedbacks)
    {
        cout << "ID: " << f.feedbackId
            << " | Rating: " << f.rating
            << " | Comment: " << f.comment
            << endl;
    }
}