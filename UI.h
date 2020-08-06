#pragma once
#include "pdcurses/curses.h"
#include <string>
//#include "common_vars.h"
class UI
{
private:
	const int MAX_SIZE = 50;
public:
	

	void c_printLogo(WINDOW*, int);
	void c_loginScreen(WINDOW*);
	void c_mainMenu(WINDOW*);
	void c_patModule(WINDOW*);
	void c_introScreen();

	//patient windows
	void c_basePatientWin(WINDOW*);
	void c_newPatientWin(WINDOW*);
	void c_viewmPatientWin(WINDOW*);
	void c_viewPatientWin(WINDOW*);
	void c_viewPatientConceptWin(WINDOW*);
	void c_viewPatientConceptNotesWin(WINDOW*);
	void c_patientLoading(WINDOW*);

	void c_baseAppoinWin(WINDOW*);
	void c_newAppointWin(WINDOW*);
	void c_viewAppointWin(WINDOW*);
	void c_viewmAppointWin(WINDOW*);
	void c_appointLoading(WINDOW*);
	void c_viewAppointConceptWin(WINDOW*);
	void c_viewAppointConceptwk123Win(WINDOW*);
	void c_viewAppointConceptwk4Win(WINDOW*);

};

