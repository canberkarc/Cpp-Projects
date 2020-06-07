#ifndef CYBERDEMONS_H
#define CYBERDEMONS_H

#include "demons.h"

namespace Canberk{
	//Definition of Cyberdemons class
	class Cyberdemons:public Demons{
			public:
				//Constructors of class
				Cyberdemons();
				
				Cyberdemons(const int stren, const int hit);

				//getDamage function of class Cyberdemons
				int getDamage();
				//getSpecies function of class Cyberdemons
				string getSpecies()const;
	};
}

#endif