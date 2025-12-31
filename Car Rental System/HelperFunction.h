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

    
    
};

#endif
#pragma once
