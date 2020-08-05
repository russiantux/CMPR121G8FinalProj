

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <strstream>
#include <iomanip>

using namespace std;




	int insertNewappointment(); 
	string welcomeScreen(); 
	struct Date; 
	struct Appointment; 
	void showAll(); int checkId(int ID);




	void editLine()
	{
		string id, appwith, day, month, year, starttime, duration, location;
		string testId;
		cout << "Enter the appointment number to be edited: ";
		cin >> testId;
		string change;
		cout << "Enter the attribute to be changed: (w for with, d for date, t for timing, l for location): ";
		cin >> change;
		fstream appointment_file;
		fstream new_file;
		new_file.open("test.txt");
		appointment_file.open("appointment.txt");
		string line;
		cout << line << endl;
		while (getline(appointment_file, line))
		{

			istringstream isstream(line);
			ostringstream test(line);

			getline(isstream, id, ';');
			if (testId == id)
			{
				cout << "It works!" << endl;
				getline(isstream, appwith, ';');
				cout << appwith;
				appwith = "test";
				getline(isstream, day, ';');
				getline(isstream, month, ';');
				getline(isstream, year, ';');
				getline(isstream, starttime, ';');
				getline(isstream, duration, ';');
				getline(isstream, location, ';');
				test << id << appwith;
				string output = test.str();
				cout << output;
				new_file >> line;
			}
		}
		system("pause");



	}





	
	int main()
	{
		int quit;
		string line;

		do
		{
			string optionSelected = welcomeScreen();

			if (optionSelected == "I" || optionSelected == "i")
			{
				int keep_going = 0;
				do
				{
					keep_going = insertNewappointment();
				} while (keep_going == 1);
				quit = 0;
			}
			else if (optionSelected == "C" || optionSelected == "c")
			{
				editLine();
				quit = 0;
			}
			else if (optionSelected == "S" || optionSelected == "s")
			{
				showAll();
				quit = 0;
			}
			else if (optionSelected == "Q" || optionSelected == "q")
			{
				cout << "Thank you for using the Appointment Module!\n";
				quit = 1;
			}
			else
			{
				cout << "Option not valid. Please try again.";
				quit = 0;
			}
		} while (quit == 0);

		system("pause");

		return 0;

	}

	

	string welcomeScreen()
	{
		string choice;
		cout << "************* Welcome to the Appointment Module *************\n\n";
		cout << "Please Select from one of the following options: \n";
		cout << "\t I - to insert new appointment info\n";
		cout << "\t C - to change the data for a particular existing appoint\n";
		cout << "\t S - to show all the appointments\n";
		cout << "\t Q - to quit this application\n";
		cout << "Please enter one of the above letters: ";
		cin >> choice;
		cout << endl;
		return choice;
	}

	struct Date
	{
		string Day;
		string Month;
		string Year;
	};

	struct Appointment
	{
		int appointmentID;
		string appointmentWith;
		Date appointmentDate;
		int appointmentStartTime;
		int appointmentDuration;
		string appointmentLocation;
	};

	int insertNewappointment()
	{
		fstream appointmentFile;
		appointmentFile.open("appointment.txt", ios::app);
		string line;
		int repeat = 0;

		cout << "Information regarding the new appointment: \n\n";

		Appointment file;
		Appointment* pointer;
		pointer = &file;

		do
		{
			cout << "Enter the appointmentID: ";
			cin >> file.appointmentID;
			getline(cin, line);
			(stringstream)line >> pointer->appointmentID;
		} while (checkId(file.appointmentID) == 1);


		cout << "\nScheduled with: ";
		getline(cin, pointer->appointmentWith);

		cout << "\nEnter the date of the appointment:";
		cout << "\n    Day(DD): ";
		getline(cin, pointer->appointmentDate.Day);
		cout << "\n    Month(MM): ";
		getline(cin, pointer->appointmentDate.Month);
		cout << "\n    Year(YYYY):";
		getline(cin, pointer->appointmentDate.Year);

		cout << "\nEnter the start time of appointment: ";
		getline(cin, line);
		(stringstream)line >> pointer->appointmentStartTime;

		cout << "\nEnter the duration of appointment (in minutes): ";
		getline(cin, line);
		(stringstream)line >> pointer->appointmentDuration;

		cout << "\nEnter the location of appointment: ";
		getline(cin, pointer->appointmentLocation);

		appointmentFile << endl << pointer->appointmentID << "; " << pointer->appointmentWith << "; " << pointer->appointmentDate.Day << "; " << pointer->appointmentDate.Month << "; " << pointer->appointmentDate.Year << "; " << pointer->appointmentStartTime << "; " << pointer->appointmentDuration << "; " << pointer->appointmentLocation << ";";

		appointmentFile.close();

		cout << "\nWould you like to enter another new appointment?\n";
		cout << "Enter 1 for yes and 0 for no: ";
		cin >> repeat;
		//getline (cin, line);
		cout << endl;

		return repeat;
	};

	void showAll()
	{
		fstream appointment_file;
		appointment_file.open("appointment.txt");

		string line;

		

		string id, appwith, day, month, year, starttime, duration, location;

		cout << setw(8) << "ID" << setw(18) << "With" << setw(5) << "Day" << setw(6) << "Month" << setw(5) << "Year" << setw(6) << "Time" << setw(10) << "Duration" << setw(15) << "Location" << endl << endl;

		while (getline(appointment_file, line))
		{

			istringstream isstream(line);

			getline(isstream, id, ';');
			getline(isstream, appwith, ';');
			getline(isstream, day, ';');
			getline(isstream, month, ';');
			getline(isstream, year, ';');
			getline(isstream, starttime, ';');
			getline(isstream, duration, ';');
			getline(isstream, location, ';');

			cout << setw(8) << id << setw(18) << appwith << setw(5) << day << setw(6) << month << setw(5) << year << setw(6) << starttime << setw(10) << duration << setw(15) << location << endl;
		}
	};

	int checkId(int ID)
	{
		fstream appointment_file;
		appointment_file.open("appointment.txt");
		string line;
		int already_used = 0;
		while (getline(appointment_file, line))
		{
			int appointmentID;
			appointment_file >> appointmentID;
			if (appointmentID == ID)
			{
				cout << "\nAn appointment with that ID already exists. Please try again.\n\n";
				already_used = 1;
				return already_used;
			}
		}
		return already_used;
	};

