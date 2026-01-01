#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

static class HelperFunctions {
public:
    
    static int calculateDays(const string& start, const string& end) {
        int sd, sm, sy, ed, em, ey;
        char sep;

        stringstream ss1(start);
        ss1 >> sd >> sep >> sm >> sep >> sy;

        stringstream ss2(end);
        ss2 >> ed >> sep >> em >> sep >> ey;

        tm tm_start = {};
        tm_start.tm_mday = sd;
        tm_start.tm_mon = sm - 1;
        tm_start.tm_year = sy - 1900;

        tm tm_end = {};
        tm_end.tm_mday = ed;
        tm_end.tm_mon = em - 1;
        tm_end.tm_year = ey - 1900;

        time_t time_start = mktime(&tm_start);
        time_t time_end = mktime(&tm_end);

        double diff = difftime(time_end, time_start);
        return static_cast<int>(diff / (60 * 60 * 24)) + 1;
    }

    
    static bool isEndDateFinished(const string& endDate) {
        int d, m, y;
        char sep;
        stringstream ss(endDate);
        ss >> d >> sep >> m >> sep >> y;

        tm endTm = {};
        endTm.tm_mday = d;
        endTm.tm_mon = m - 1;
        endTm.tm_year = y - 1900;

        time_t endTime = mktime(&endTm);
        time_t now = time(nullptr);

        return difftime(now, endTime) >= 0;
    }

    ///////////////////////////////////////////////
    static bool isValidDateFormat(const string& date) {
        int d, m, y;
        char sep1, sep2;
        stringstream ss(date);

        ss >> d >> sep1 >> m >> sep2 >> y;
        return (!ss.fail() && sep1 == '-' && sep2 == '-' &&
            d >= 1 && d <= 31 &&
            m >= 1 && m <= 12 &&
            y >= 1900);
    }

    // ==============================
    // Check if date is in the future
    // ==============================
    static bool isDateInFuture(const string& date) {
        int d, m, y;
        char sep;
        stringstream ss(date);
        ss >> d >> sep >> m >> sep >> y;

        tm dateTm = {};
        dateTm.tm_mday = d;
        dateTm.tm_mon = m - 1;
        dateTm.tm_year = y - 1900;

        time_t inputTime = mktime(&dateTm);

        tm todayTm = {};
        time_t now = time(nullptr);
        localtime_s(&todayTm, &now);
        todayTm.tm_hour = 0;
        todayTm.tm_min = 0;
        todayTm.tm_sec = 0;

        time_t today = mktime(&todayTm);

        return difftime(inputTime, today) > 0;
    }

    // ==============================
    // Validate start & end dates
    // ==============================
    static bool validateStartEndDates(const string& start, const string& end) {

        if (!isValidDateFormat(start) || !isValidDateFormat(end)) {
            cout << "Invalid format. Use DD-MM-YYYY\n";
            return false;
        }

        if (!isDateInFuture(start) || !isDateInFuture(end)) {
            cout << "Dates must be in the future\n";
            return false;
        }

        int days = calculateDays(start, end);
        if (days <= 0) {
            cout << " Start date must be before end date\n";
            return false;
        }

        return true;
    }
};

#endif
#pragma once
