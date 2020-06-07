#include "creature.h"
using namespace std;

namespace Canberk{
	//Constructors
	Creature::Creature() {
		type = 0;
		strength = 10;
		hitPoint = 10;
	}

	Creature::Creature(const int newS,const int newH) {//Contructor with parameters
		type = 0;
		strength = newS;
		hitPoint = newH;
	}	

	Creature::Creature(const int newType, const int newStrength, const int newHit){//Contructor with parameters
			type = newType;
			strength = newStrength;
			hitPoint = newHit;
	}
	//Setter and getter functions
	int Creature::setType(const int t){ type = t;}

	int Creature::getType()const{return type;}

	int Creature::setStrength(const int s){ strength = s;}

	int Creature::getStrength()const{return strength;}

	int Creature::setHitP(const int hp){hitPoint = hp;}

	int Creature::getHitP()const{return hitPoint;}

				
	//Function to get type of creature
	string Creature::getSpecies()const
	{
		if(getType() == 0) return "Human";
	}

	//getDamage function which is used for creatures
	int Creature::getDamage() const {

		int damage;

		damage = (rand() % getStrength()) + 1;

		return damage;
	}

}