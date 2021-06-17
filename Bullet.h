#ifndef _BULLET_H__
#define _BULLET_H__

#include"Entity.h"
#include"Monster.h"




class Bullet : public Entity {
public:
	
	CREATE_FUNC(Bullet);
	virtual bool init();
public:
	void MovebyLine();//子弹沿线移动
	void Fade();//碰壁打人消失
	float numx; float numy; int S;//通过方向向量确定轨迹
	int Bullet_accuracy=7;//子弹准度
	bool is_hit_Monster(Monster* monster);
	/*bool is_hit_Hero(Hero* hero);*/

	bool isNeedFade= false;//判断是否需要消失
};
#endif // !_BULLET_H__


