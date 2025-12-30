//#include "AuthService.h"
//#include "User.h" 
//#include "Customer.h"
//#include <fstream>
//#include <sstream>
//#include<iostream>
//using namespace std;
//
//
//User* AuthService::authenticate(const string& username, const string& password) {
//
//    fstream file("users.txt", ios::in);
//
//    if (!file.is_open()) {
//        cout << "failed\n";
//        return nullptr;
//    }
//
//    //beginning f
//    file.seekg(0, ios::beg);
//
//    string line;
//    while (getline(file, line)) {
//        string idStr, u, p, roleStr;
//        stringstream ss(line);
//
//        getline(ss, idStr, ',');
//        getline(ss, u, ',');
//        getline(ss, p, ',');
//        getline(ss, roleStr, ',');
//
//        int role = stoi(roleStr);
//
//        cout << u << " | " << p << " | " << role << endl;
//
//        if (u == username && p == password) {
//            if (role == 0) return new Customer();
//        }
//    }
//
//    return nullptr;
//}

#include "AuthService.h"
#include "Customer.h"
#include "Manager.h"
//#include "Driver.h"
#include <fstream>
#include <sstream>

User* AuthService::authenticate(const string& username, const string& password) {

    fstream users("users.txt", ios::in);
    string line;

    while (getline(users, line)) {
        string idStr, u, p, roleStr;
        stringstream ss(line);

        getline(ss, idStr, ',');
        getline(ss, u, ',');
        getline(ss, p, ',');
        getline(ss, roleStr, ',');

        if (u == username && p == password) {
            int userId = stoi(idStr);
            int role = stoi(roleStr);

            if (role == Role_Customer) {
                // read from customers.txt
                fstream customers("customers.txt", ios::in);
                string cline;

                while (getline(customers, cline)) {
                    stringstream css(cline);
                    string cid, uid, name, phone, nid;

                    getline(css, cid, ',');
                    getline(css, uid, ',');
                    getline(css, name, ',');
                    getline(css, phone, ',');
                    getline(css, nid, ',');

                    if (stoi(uid) == userId) {
                        return new Customer(
                            userId,
                            username,
                            name,
                            phone,
                            nid
                        );
                    }
                }
            }
            else if (role == Role_Manager) {
                return new Manager(userId, username);
            }
            //else if (role == Role_Driver) {
            //   // return new Driver(userId, username);
            //}
        }
    }
    return nullptr;
}