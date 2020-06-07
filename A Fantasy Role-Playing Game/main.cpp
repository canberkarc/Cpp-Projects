#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//Including .h files of classes
#include "creature.h"
#include "demons.h"
#include "human.h"
#include "balrogs.h"
#include "cyberdemons.h"
#include "elf.h"

using namespace Canberk; //Including namespace

int main(){
	srand(time(NULL));
	//Objects 
	Elf e(90,70);
	Balrogs b(100,20);
	Human h(40,60);
	Cyberdemons c(10,50);

	//Damages of objects
	for(int i=0; i<10; ++i){
		e.getDamage();
		b.getDamage();
		c.getDamage();
		h.getDamage();
		cout << endl << endl;
	}
}