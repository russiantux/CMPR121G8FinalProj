#pragma once
#include <string>
#include "common_vars.h"

class patient
{
private:
	//p ~ patient general info
	std::string p_lName;
	std::string p_fName;
	char p_mInit;
	int p_Age;
	Months p_dobMonth;
	int p_dobDay;
	int p_dobYear;
	Y_N p_isMinor;
	Gender p_Gender;
	MaritalStat p_MaritalStat;

	std::string p_PCP;
	int p_PCPnum;
	std::string p_refPhys;
	int p_refPhysNum;
	
	//a ~ patient address
	int a_hNum;
	std::string a_Address;
	std::string a_City;
	char* a_State[2];
	int a_Zip;

	//ph ~ patient phone/contact
	int ph_Home;
	int ph_Work;
	std::string ph_eMail;
	cMethod ph_cMethod;
	Y_N ph_canText;

	//i ~ patient insurance
	std::string i_insuranceName;
	int i_billingNum;
	std::string i_billingAddress;
	int i_iID;

	//e ~ emergency contact
	std::string e_contName;
	int e_contPhone;
	Relationship e_contRel;

	struct pCodes {
		char* icd[4];
		std::string pCode_refUsr;
		Months pCode_mAdded;
		int pCode_dAdded;
		int pCode_yAdded;
	};

	

public:
	typedef int patientID;

	//base patient struct
	struct bPATIENT {
		//p ~ patient general info
		
			std::string p_lName;
			std::string p_fName;
			char p_mInit;
			int p_Age;
			Months p_dobMonth;
			int p_dobDay;
			int p_dobYear;
			Y_N p_isMinor;
			Gender p_Gender;
			MaritalStat p_MaritalStat;
		
	

		std::string p_PCP;
		int p_PCPnum;
		std::string p_refPhys;
		int p_refPhysNum;

		//a ~ patient address
		int a_hNum;
		std::string a_Address;
		std::string a_City;
		char* a_State[2];
		int a_Zip;

		//ph ~ patient phone/contact
		int ph_Home;
		int ph_Work;
		std::string ph_eMail;
		cMethod ph_cMethod;
		Y_N ph_canText;

		//i ~ patient insurance
		std::string i_insuranceName;
		int i_billingNum;
		std::string i_billingAddress;
		int i_iID;

		//e ~ emergency contact
		std::string e_contName;
		int e_contPhone;
		Relationship e_contRel;

		pCodes p_Codes[MAX_SIZE];
	};

	void addPatient(bPATIENT* p);

	std::string p_getfName(patientID*);
	std::string p_getlName(patientID*);
	char* p_getMiName(patientID*);
	int p_getAge(patientID*);
	int p_getDoB(patientID*);
	char p_getGender(patientID*);
	std::string p_getPCP(patientID*);
	std::string p_getRefPhys(patientID*);
	int p_getContact(patientID*);
	std::string p_getWPhone(patientID*);
	std::string p_geteMail(patientID*);

};

