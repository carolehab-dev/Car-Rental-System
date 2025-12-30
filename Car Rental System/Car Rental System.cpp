#include <conio.h>
#include <iostream>
#include "AuthService.h"
#include "Customer.h"
using namespace std;

int showMainMenu() {
    const char* options[] = {
        "Login",
        "Register (Customer Only)",
        "Exit"
    };

    int selected = 0;

    while (true) {
        system("cls");
        cout << "====== CAR RENTAL SYSTEM ======\n\n";

        for (int i = 0; i < 3; i++) {
            if (i == selected)
                cout << " > " << options[i] << endl;
            else
                cout << "   " << options[i] << endl;
        }
        char key = _getch();
        if (key == 72 && selected > 0) selected--;
        else if (key == 80 && selected < 2) selected++;
        else if (key == 13) return selected; 
    }
}

int main() {
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


//GUI 