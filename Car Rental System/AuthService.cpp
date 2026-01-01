#include "AuthService.h"
#include "Customer.h"
#include "Manager.h"
#include "Driver.h"
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
            else if (role == Role_Driver)
            {
                fstream drivers("drivers.txt", ios::in);
                string dline;

                while (getline(drivers, dline))
                {
                    stringstream ds(dline);
                    string driverId, uid, uname, phone, statusStr;

                    getline(ds, driverId, ',');
                    getline(ds, uid, ',');
                    getline(ds, uname, ',');
                    getline(ds, phone, ',');
                    getline(ds, statusStr);

                    if (stoi(uid) == userId)
                    {
                        return new Driver(
                            stoi(driverId),   // driverId
                            userId,           // userId
                            username,
                            phone,
                            "driver",
                            "",
                            statusStr == "1"
                        );
                    }
                }
            }
        }
    }
    return nullptr;
}