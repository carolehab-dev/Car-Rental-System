#pragma once
#include "User.h"

class AuthService
{
public:
	static User* authenticate(const string& username, const string& password);

};

