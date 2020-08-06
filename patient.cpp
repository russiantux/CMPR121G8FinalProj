#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "patient.h"

using namespace std;


void Patient::addPatient(){
	Patient patientInfo;
	
		string firstName;
	string lastName;
	string provider;
	int phoneNumber;
	int age;
	

	

	
	char userCont;

	bool end = false;
	fstream saveFile;

	p_lName = firstName;
	p_fName = lastName;
	ph_Phone = phoneNumber;
	ph_Phone = phoneNumber;
	p_Age = age;
	i_insuranceName = provider;

	while (end == false)
	{
		saveFile.open("database.txt", ios::out);

		//write user info to file
		cout << "\n****** PLEASE ENTER THE FOLLOWING INFORMATION *****\n" << endl;

		cout << "please enter first name\n" << endl;
		cin >> firstName;
		saveFile << firstName << setw(5);

		cout << "please enter last name\n" << endl;
		cin >> lastName;
		saveFile << lastName << setw(5);

		cout << "please enter phone number\n" << endl;
		cin >> phoneNumber;
		saveFile << phoneNumber << setw(5);

		cout << "please enter patient age\n" << endl;
		cin >> age;
		saveFile << age << setw(5);

		cout << "please enter patients insurance provider\n" << endl;
		cin >> provider;
		saveFile << provider << endl;

		//patientInfo.addPatient(firstName, lastName, phoneNumber, age, provider);

		//continue?
		cout << "press Y to add another patient or any other button to exit" << endl << endl;
		cin >> userCont;

		if (userCont == 'Y' | userCont == 'y')
		{
			//continue the loop
			bool end = false;
			//return  -1;

		}
		else {
			//end the while loop
			bool end = true;
			//return 1;
		}
	}

	saveFile.close();
	
};




