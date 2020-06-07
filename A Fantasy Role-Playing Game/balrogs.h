#ifndef BALROGS_H
#define BALROGS_H

#include "demons.h"

namespace Canberk{
	//Derived Balrogs class definition
	class Balrogs:public Demons{
			public:
				Balrogs(); //Default constructor

				Balrogs(const int stren, const int hit);//Constructor with parameters

				int getDamage();// getDamage function of Balrogs
				string getSpecies()const; //getSpecies function of class Balrogs
	};	
}

#endif