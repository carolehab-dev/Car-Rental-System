#include <iostream>
#include <fstream>
#include <sstream>
#include "Cars.h"
#include "File.h"
#include <iomanip>
#include <conio.h>
#include <windows.h>
vector<Cars> Cars::allCars;
static const int TABLE_WIDTH = 86;
static const int COL_PAD = 2;
Cars::Cars(){}
static int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
static void clearScreen()
{
    system("cls");
}
static void printCarTableHeader(int leftPad)
{cout << string(leftPad, ' ')<< "+" << string(TABLE_WIDTH, '-') << "+\n";
cout << string(leftPad, ' ')<< "| "<< left << setw(4) << "ID" << string(COL_PAD, ' ')<< setw(16) << "MODEL" << string(COL_PAD, ' ')<< setw(12) << "COLOR" << string(COL_PAD, ' ')<< setw(12) << "CAR NO" << string(COL_PAD, ' ')<< setw(14) << "RENT COST" << string(COL_PAD, ' ')<< setw(12) << "STATUS"<< " |\n";
cout << string(leftPad, ' ')<< "+" << string(TABLE_WIDTH, '-') << "+\n";
}
void Cars::viewAllCars()
{
    if (allCars.empty())
    {
        cout << "No cars available.\n";
        return;
    }

    int selected = 0;
    int tableWidth = 74; // total width of the table
    int consoleWidth = getConsoleWidth();
    int leftPad = (consoleWidth - tableWidth) / 2;
    if (leftPad < 0) leftPad = 0;

    while (true)
    {
        system("cls");

        // Centered title
        cout << "\n";
        int titlePad = (TABLE_WIDTH - 17) / 2; // 17 = length of "LIST OF CARS"
        cout << string(leftPad, ' ')
            << string(titlePad, ' ') << "=== LIST OF CARS ===\n\n";
        printCarTableHeader(leftPad);

        for (int i = 0; i < allCars.size(); i++)
        {
            const Cars& c = allCars[i];
            cout << string(leftPad, ' ') << "| ";
            // Cursor 
            if (i == selected)
                cout << ">> ";
            else
                cout << "   ";

            cout << left<< setw(2) << c.carId << string(COL_PAD, ' ')<< setw(16) << c.model << string(COL_PAD, ' ')<< setw(12) << c.color << string(COL_PAD, ' ')<< setw(12) << c.carNum << string(COL_PAD, ' ')
                << setw(14) << c.carRentalCost << string(COL_PAD, ' ')
                << setw(12) << (c.availibility_status ? "Available" : "Rented") << " |\n";
        }
        cout << string(leftPad, ' ')<< "+" << string(TABLE_WIDTH, '-') << "+\n";

        cout << "\n";
        cout << string(leftPad, ' ')<< "Up and Down = Navigate | ENTER = Details | ESC = Exit\n";
        char key = _getch();
        if (key == 72 && selected > 0)                       // Up
            selected--;
        else if (key == 80 && selected < allCars.size() - 1) // Down
            selected++;
        else if (key == 13)                                  // Enter
        {
            viewCarInfo(allCars[selected].carId);
            _getch();
        }
        else if (key == 27)                                  // Ese
            break;
    }
}
void Cars::viewCarInfo(int id)
{
    system("cls");
    int consoleWidth = getConsoleWidth(); // for centering
    int leftPad = (consoleWidth - 40) / 2;
    if (leftPad < 0) leftPad = 0;
    for (const auto& c : allCars)
    {
        if (c.carId == id)
        {
            cout << "\n";
            cout << string(leftPad, ' ') << "=== CAR DETAILS ===\n\n";
            cout << string(leftPad, ' ') << "Car ID      : " << c.carId << endl;
            cout << string(leftPad, ' ') << "Model       : " << c.model << endl;
            cout << string(leftPad, ' ') << "Color       : " << c.color << endl;
            cout << string(leftPad, ' ') << "Car Number  : " << c.carNum << endl;
            cout << string(leftPad, ' ') << "Rental Cost : " << c.carRentalCost << endl;
            cout << string(leftPad, ' ') << "Status      : "<< (c.availibility_status ? "Available" : "Not Available")<< endl;
            return;
        }
    }
    cout << "Car not found.\n";
}

//void Cars::viewAllAvaliableCars()
//{
//   allCars.clear(); // added carol
//    readFromFile("cars.csv", allCars); //  added carol
//    cout << "\n--- List of All Availiable Cars ---\n";
//    for (const auto &c : allCars)
//    {
//        if (c.availibility_status == 1)
//        {
//            cout << "ID: " << c.carId
//                 << " | Model: " << c.model
//                 << " | Color: " << c.color
//                 << " | Car Number: " << c.carNum
//                 << " | Rental Cost: " << c.carRentalCost
//                 << " | Status: " << c.availibility_status
//                 << endl;
//        }
//    }
//}
void Cars::viewAllAvaliableCars()
{
    allCars.clear();
    readFromFile("cars.csv", allCars);

    vector<Cars> availableCars;
    for (const auto& c : allCars)
        if (c.availibility_status == 1)
            availableCars.push_back(c);

    if (availableCars.empty())
    {
        cout << "No available cars.\n";
        return;
    }

    allCars = availableCars;   // for reusing all tepmate of the table
    viewAllCars();
}