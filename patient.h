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
		void addPatient();
};

#endif // !PATIENT_H



