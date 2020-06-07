#include "balrogs.h"
using std::cout;

namespace Canberk{
	
	Balrogs::Balrogs():Demons(){ //Default constructor
		setType(2);
	}

	Balrogs::Balrogs(const int stren,const int hit):Demons(stren,hit){//Constructor with parameters
		setType(2);
	}
	//getSpecies function of class Balrogs
	string Balrogs::getSpecies()const{
		if(getType() == 2)
			return "Balrog";
	}

	//getDamage function for Balrogs
	int Balrogs::getDamage(){
		int damage = Demons::getDamage();
		// Balrogs are so fast they get to attack twice
		int damage2 = (rand() % getStrength()) + 1;
		
		cout << "\n" << getSpecies() << " attacks for " << damage << " points!";
    	cout << "\nAdditional " << damage2 << " damage points " << "for Balrog speed attack!" << "\n";
    	damage += damage2;	

    	cout << "Total damage: " << damage << "\n";

    	return damage;
	}
}