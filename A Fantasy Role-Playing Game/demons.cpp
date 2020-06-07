#include "demons.h"
using std::cout;

namespace Canberk{	
	//Constructors of class
	Demons::Demons():Creature(){

	}

	Demons::Demons(const int stren, const int hit):Creature(stren, hit){
	}

	//description of getDamage function of Demons class
	int Demons::getDamage(){
		int damage = Creature::getDamage();
		
		int chanDemon = (rand() % 20) + 1;
		if(chanDemon == 5){
			cout << "\n+50 Damage Points for Demonic Attack";
			damage += 50;
		}

		return damage;
	}
}