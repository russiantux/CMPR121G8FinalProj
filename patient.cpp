#include "patient.h"


//adding a new patient, takes a struct* of all the data
void patient::addPatient(bPATIENT* p) {
	//see patient_struct_format.md to see the format in which this takes information
	//god i hate the way this is, but i don't have enough time to make it nicer. too bad!
	
	//non-enum
	p->p_lName = p_lName;
	p->p_fName = p_fName;
	p->p_mInit = p_mInit;
	p->p_Age = p_Age;

	p->p_dobMonth = p_dobMonth;
	p->p_dobDay = p_dobDay;
	p->p_dobYear = p_dobYear;
	p->p_isMinor = p_isMinor;
	p->p_Gender = p_Gender;
	p->p_MaritalStat = p_MaritalStat;

	p->p_PCP = p_PCP;
	p->p_PCPnum = p_PCPnum;
	p->p_refPhys = p_refPhys;
	p->p_refPhysNum = p_refPhysNum;

	p->a_hNum = a_hNum;
	p->a_Address = a_Address;
	p->a_City = a_City;
	p->a_State - a_State;
	p->a_Zip = a_Zip;


	//enum's
	

};