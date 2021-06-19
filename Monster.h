#include"Entity.h"

class Monster : public Entity {
public:
	
	CREATE_FUNC(Monster);
	virtual bool init();
public:
	void show();
	/*void hide();
	void rest();
	void isAlive();*/
private:
	bool m_isAlive;
};
