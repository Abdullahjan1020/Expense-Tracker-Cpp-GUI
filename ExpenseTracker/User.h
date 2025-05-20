#pragma once
using namespace System;
public ref class User {
public:
	String^ Username;
	String^ Password;
	User(String^ username, String^ password) {
		Username = username;
		Password = password;
	}
};