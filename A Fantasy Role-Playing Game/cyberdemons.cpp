#include "cyberdemons.h"
using std::cout;

namespace Canberk{
	//Constructors of class
	Cyberdemons::Cyberdemons():Demons(){
		setType(1);
	}
	
	Cyberdemons::Cyberdemons(const int stren, const int hit):Demons(stren,hit){
		setType(1);
	}	

	//getSpecies function of class Cyberdemons
	string Cyberdemons::getSpecies()const{
		if(getType() == 1)
			return "Cyberdemons";
	}


	//description of getDamage function of Cyberdemons class
	int Cyberdemons::getDamage(){
		int damage = Demons::getDamage();
		cout << "\n" << getSpecies() << " attacks for " << damage << " points!";
		cout << "\nTotal damage: " << damage << "\n";

		return damage;
	}
}