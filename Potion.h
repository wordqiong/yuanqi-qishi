
#ifndef _POTION_H__
#define _POTION_H__
#include<iostream>
#include<string>
#include "Entity.h"

using namespace std;

class Potion : public Entity {
public:
	virtual bool init();

	CREATE_FUNC(Potion);

	int bloodRecover = 2;//»Ø¸´ÉúÃüÖµ
	int type = 1;
	bool is_can_be_used = true;
	string load1 = "Potion";
	string load3 = ".png";
	string final_load;
	
};


#endif // !_POTION_H__
