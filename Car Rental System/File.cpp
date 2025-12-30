#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>
#include "../include/File.h"
#include "../include/Cars.h"

template <typename T>
void File<T>::readFromFile(const string &filename, vector<T> &temp)
{
    if (filename == "cars.csv")
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "ERROR: Cannot open file '" << filename << "'" << endl;
            cout << "   - Make sure the file exists in: " << endl;
            cout << "     D:\\ITI\\SWE\\Car_Rental\\cars.csv" << endl;
            cout << "   - Check spelling and extension (.csv)" << endl;
            return;
        }
        string line;
        getline(file, line);

        while (getline(file, line))
        {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            if (line.empty())
                continue;
            stringstream ss(line);
            string token;
            vector<string> data;

            while (getline(ss, token, ','))
            {
                data.push_back(token);
            }

            Cars c;
            c.carId = stoi(data[0]);
            c.model = data[1];
            c.color = data[2];
            c.carNum = stoi(data[3]);
            c.availibility_status = stoi(data[4]);
            c.carRentalCost = stod(data[5]);

            temp.push_back(c);
        }
        file.close();
    }
};
template <typename T>
void File<T>::appendToFile(const string &filename, const T &temp)
{
    if (filename == "cars.csv")
    {
        fstream file(filename, ios::in | ios::out | ios::app);
        if (!file.is_open())
        {
            cout << "Error: Could not open " << filename << " for appending!\n";
            return;
        }

        file.seekp(0, ios::end);
        streampos fileSize = file.tellp();

        if (fileSize == 0)
        {

            if constexpr (std::is_same_v<T, Cars>)
            {
                file << "carId,model,color,carNum,availibility_status,carRentalCost\n";
            }
        }
        else if (fileSize > 0)
        {

            file.seekg(-1, ios::end);
            char lastChar;
            file.get(lastChar);

            file.seekp(0, ios::end);

            if (lastChar != '\n' && lastChar != '\r')
            {
                file << "\n";
            }
        }
        if constexpr (std::is_same_v<T, Cars>)
        {
            file << temp.carId << ","
                 << temp.model << ","
                 << temp.color << ","
                 << temp.carNum << ","
                 << (temp.availibility_status ? "1" : "0") << ","
                 << temp.carRentalCost << "\n";
        }

        file.close();
        cout << "Car added successfully to file with ID: " << temp.carId << endl;
    }
}
template <typename T>
void File<T>::saveToFile(const string &filename, vector<T> &temp)
{
    if (filename == "cars.csv")
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open " << filename << " for appending!\n";
            return;
        }

        for (const auto &c : temp)
        {
            file << c.carId << ","
                 << c.model << ","
                 << c.color << ","
                 << c.carNum << ","
                 << (c.availibility_status ? "1" : "0") << ","
                 << c.carRentalCost << "\n";
        }

        file.close();
    }
}
template class File<Cars>;