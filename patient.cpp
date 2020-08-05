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
	char userCont;
	bool end = false;

	fstream saveFile;

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

		patientInfo.addPatient(firstName, lastName, phoneNumber, age, provider);

		//continue?
		cout << "press Y to add another patient or any other button to exit" << endl << endl;
		cin >> userCont;

		if (userCont == 'y' | userCont == 'Y')
		{
			//continue the loop
			bool end = false;
			return  end;

		}
		else {
			//end the while loop
			bool end = true;
			return end;
		}
	}

	saveFile.close();
	return 0;
};




