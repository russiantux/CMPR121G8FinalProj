#pragma once
#include <string>

using namespace std;
#ifndef PATIENT_H
#define PATIENT_H

class Patient
{
	private:
		//p ~ patient general info
		string p_lName;
		string p_fName;
		string i_insuranceName;
		int p_Age;
		int ph_Phone;

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

#endif // !PATIENT_H



