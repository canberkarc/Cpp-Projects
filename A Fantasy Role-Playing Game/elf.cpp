#include "elf.h"
using std::cout;

namespace Canberk{
	//Constructors of class
	Elf::Elf():Creature(){
		setType(3);
	}

	Elf::Elf(const int stren, const int hit):Creature(3,stren,hit){
		/*Deliberately empty*/
	}

	//getSpecies function of class Elf
	string Elf::getSpecies()const{
		if(getType() == 3){
			return "Elf";
		}
	}

	//description of getDamage function of Elf class
	int Elf::getDamage(){
		int damage = Creature::getDamage();
		// All creatures inflict damage which is a
		// random number up to their strength
		// Elves inflict double magical damage with a 10% chance
			int chanElf = (rand() % 10) + 1;
			if(chanElf == 5) {
				damage *= 2;
				cout << "\nDouble magical damage for Elf Attack!";
			}
			cout << "\n" << getSpecies() << " attacks for " << damage << " points!";
			cout << "\nTotal damage: " << damage << "\n";

			return damage;
	}
}