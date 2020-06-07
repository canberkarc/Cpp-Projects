#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
using std::string;

namespace Canberk{
	//Base class definition
	class Creature{
		public:
			Creature(); //Default constructor
			
			Creature(const int newStrength, const int newHit);//Contructor with parameters
			
			Creature(const int newType, const int newStrength, const int newHit);//Contructor with parameters
				
			int getDamage()const;

			string getSpecies()const;

			//Setter and getter functions for private values
			int setType(const int t);
			int getType()const;
			int setStrength(const int s);
			int getStrength()const;
			int setHitP(const int hp);
			int getHitP()const;

		private:
			int type;
			int strength;
			int hitPoint;
	};
}

#endif