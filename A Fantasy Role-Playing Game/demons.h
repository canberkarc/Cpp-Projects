#ifndef DEMONS_H
#define DEMONS_H

#include "creature.h"

namespace Canberk{
	//Definition of Demons class
	class Demons:public Creature{
			public:
				//Constructors of class
				Demons();				

				Demons(const int stren, const int hit);
				//getDamage function of class
				int getDamage();
	};
}

#endif 