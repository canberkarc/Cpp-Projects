#ifndef HUMAN_H
#define HUMAN_H

#include "creature.h"

namespace Canberk{
	//Definition of Human class
	class Human:public Creature{
			public:
				//Constructors of class
				Human();

				Human(const int stren, const int hit);

				//getSpecies function of class 
				string getSpecies()const;

				//getDamage function of class
				int getDamage();
	};
}

#endif