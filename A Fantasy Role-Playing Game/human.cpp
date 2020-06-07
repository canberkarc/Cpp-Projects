#include "human.h"
using std::cout;

namespace Canberk{
	//Constructors of class
	Human::Human():Creature(){
		setType(0);
	}

	Human::Human(const int stren, const int hit):Creature(0,stren,hit){
		/*Deliberately empty*/
	}

	//getSpecies function of class Human
	string Human::getSpecies()const{
		if(getType() == 0)
			return "Human";
	}

	//description of getDamage function of Human class
	int Human::getDamage(){
		int damage = Creature::getDamage();
		cout << "\n" << getSpecies() << " attacks for " << damage << " points!";
		cout << "\nTotal damage: " << damage << "\n";
		
		return damage;
	}
}