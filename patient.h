#pragma once
#include <string>
//#include "common_vars.h"

using namespace std;

class Patient
{
private:
	//p ~ patient general info
	string p_lName;
	string p_fName;
	int p_Age;
	int ph_Phone;
	string i_insuranceName;

	double icdCode;
public:
	typedef int patientID;

	void addPatient(string firstName, string lastName, int phoneNumber, int age, string provider)
	{
		p_lName = firstName;
		p_fName = lastName;
		ph_Phone = phoneNumber;
		ph_Phone = phoneNumber;
		p_Age = age;
		i_insuranceName = provider;
	};
};



