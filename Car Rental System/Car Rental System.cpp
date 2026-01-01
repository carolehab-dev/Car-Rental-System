#include <conio.h>
#include <iostream>
#include "AuthService.h"
#include "Customer.h"
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include "Cars.h"
using namespace std;
#define CYAN  "\033[1;36m"
#define GREY  "\033[90m"
#define RESET "\033[0m"

void printBigTitleCentered(int consoleWidth) {
    vector<string> title = {
        "  ____    _    ____    ____  _____ _   _ _____ ",
        " / ___|  / \\  |  _ \\  |  _ \\| ____| \\ | |_   _|",
        "| |     / _ \\ | |_) | | |_) |  _| |  \\| | | |  ",
        "| |___ / ___ \\|  _ <  |  _ <| |___| |\\  | | |  ",
        " \\____/_/   \\_\\_| \\_\\ |_| \\_\\_____|_| \\_| |_|  "
    };
    int verticalPadding = 2;
    for (int i = 0; i < verticalPadding; i++) cout << endl;

    for (auto& line : title) {
        int pad = (consoleWidth - line.length()) / 2;
        if (pad < 0) pad = 0;
        cout << string(pad, ' ') << CYAN << line << RESET << endl;
    }
}
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
void printCentered(const string& text, int consoleWidth) {
    int padding = (consoleWidth - text.length()) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << text << endl;
}
void drawLoadingBar(int progress, int width) {
    int consoleWidth = getConsoleWidth();
    int filled = (progress * width) / 100;
    string bar = "[";
    for (int i = 0; i < width; i++)
        bar += (i < filled ? "*" : " ");
    bar += "] " + to_string(progress) + "%";

    printCentered(bar, consoleWidth);
}
void updateFrame(int pos, int width) {
    cout << "\033[H";

    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int centerPadding = (consoleWidth - width) / 2;
    if (centerPadding < 0) centerPadding = 0;
    int verticalStart = (consoleHeight / 2) - 8;
    if (verticalStart < 0) verticalStart = 0;
    // Move cursor down to vertical center
    cout << string(verticalStart, '\n');
    printBigTitleCentered(consoleWidth);
    cout << endl;
    vector<string> car = {
        "             _______          ",
        "         ___//__][__\\___      ",
        "        /               \\     ",
        "       '--_(@)-------(@)_--'  "
    };

    cout << string(centerPadding, ' ') << GREY << string(width, '=') << RESET << endl;
    for (auto& line : car) {
        cout << string(centerPadding + pos, ' ') << line << endl;
    }
    string road;
    for (int i = 0; i < width; i++)
        road += ((i + pos) % 8 < 4) ? "_" : " ";
    cout << string(centerPadding, ' ')
   << GREY << road << RESET << endl;
}
void showIntro() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\033[?25l"; // hide cursor

    int pos = 0;
    int totalFrames = 80;
    for (int i = 0; i < 80; i++) {
        updateFrame(pos, 65);
        int progress = (i * 100) / totalFrames;
        cout << endl;
        drawLoadingBar(progress, 30);
        pos = (pos + 1) % 35;
        this_thread::sleep_for(chrono::milliseconds(60));
    }

    cout << "\033[?25h"; // show cursor
}
int showMainMenu() {
    const char* options[] = {
        "Login",
        "Register (Customer Only)",
        "Exit"
    };
    int selected = 0;
    while (true) {
        system("cls");
        int consoleWidth = getConsoleWidth();
        int width = 40;
        int leftPadding = (consoleWidth - width - 2) / 2;

        cout << string(leftPadding, ' ') << "+" << string(width, '-') << "+\n";
        cout << string(leftPadding, ' ') << "|      CAR RENTAL SYSTEM MENU            |\n";
        cout << string(leftPadding, ' ') << "+" << string(width, '-') << "+\n";

        for (int i = 0; i < 3; i++) {
            cout << string(leftPadding, ' ') << "| ";
            if (i == selected)
                cout << "> " << options[i];
            else
                cout << "  " << options[i];

            cout << string(width - strlen(options[i]) - 4, ' ') << " |\n";
        }

        cout << string(leftPadding, ' ') << "+" << string(width, '-') << "+\n";

        char key = _getch();
        if (key == 72 && selected > 0) selected--;        // Up
        else if (key == 80 && selected < 2) selected++;  // Down
        else if (key == 13) return selected;              //Enter
    }
}

int main() {
    showIntro();
    Cars::updateCarsStatus();
    while (true) {
        int choice = showMainMenu();
        if (choice == 0) {
            system("cls");
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            User* user = AuthService::authenticate(username, password);
            if (user) {
                user->login();
                user->showMenu();
                delete user;
            }
            else {
                cout << "Login failed!\n";
                system("pause");
            }
        }
        else if (choice == 1) {
            system("cls");
            Customer::Register();
            system("pause");
        }
        else {
            cout << "Thank You for Using Our System\n";
            break;
        }
    }
    return 0;
}
