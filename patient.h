#pragma once
#include <string>

class patient
{
private:
	//p ~ patient general info
	std::string p_lName;
	std::string p_fName;
	char p_mInit;
	int p_Age;
	enum p_dobMonth {JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEPT,OCT,NOV,DEC};
	int p_dobDay;
	int p_dobYear;
	enum p_isMinor {YES,NO};
	enum p_Gender {MALE,FEMALE};
	enum p_MaritalStat {MARRIED,SINGLE,DIVORCED,WINDOWED,SEP};

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
	enum ph_cMethod { HOME, WORK,EMAIL};
	enum ph_canText {YES,NO};

	//i ~ patient insurance
	std::string i_insuranceName;
	int i_billingNum;
	std::string i_billingAddress;
	int i_iID;

	//e ~ emergency contact
	std::string e_contName;
	int e_contPhone;
	enum e_contRel {FAMILY,FRIEND,CLOSE};

	struct pCodes {
		char* icd[4];
		std::string pCode_refUsr;
		enum pCode_mAdded { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC };
		int pCode_dAdded;
		int pCode_yAdded;
	};

};

