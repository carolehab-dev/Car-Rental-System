#pragma once
#include <string>
using namespace std;
enum Role {
	Role_Customer=0 ,
	Role_Manager=1 ,
	Role_Driver=2

};
class User
{public:
	virtual bool login() = 0; // pure virtual 
	virtual void showMenu()=0;// pure virtual  
	virtual ~User() {}
	int getUserId() const { return user_Id; }
protected:
	int	user_Id;
	string userName;
	string password;
	Role role;
};

