#ifndef ELF_H
#define ELF_H


#include "creature.h"
#include "demons.h"

namespace Canberk{
	//Definition of class Elf
	class Elf:public Creature{
			public:
				//Constructors of class
				Elf();

				Elf(const int stren, const int hit);

				//getSpecies function of class Elf
				string getSpecies()const;

				//getDamage function for class Elf
				int getDamage();
	};
}

#endif