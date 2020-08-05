#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "patient.h"

using namespace std;

int main()
{
	Patient patientInfo;

	string firstName;
	string lastName;
	string provider;
	int phoneNumber;
	int age;

	fstream saveFile;
	saveFile.open("database.txt", ios::out);
	
	//write user info to file
	cout << "please enter the following information" << endl;

	cout << "please enter first name" <<endl;
	cin >> firstName;

	cout << "please enter last name" << endl;
	cin >> lastName;
	 
	cout << "please enter phone number" << endl;
	cin >> phoneNumber;

	cout << "please enter patient age" << endl;
	cin >> age;

	cout << "please enter patients insurance provider" << endl;
	cin >> provider;

	patientInfo.addPatient(firstName, lastName, phoneNumber, age, provider);
	
	saveFile << firstName << lastName << ": " << phoneNumber << age << provider << endl;

	return 0;
};
