#ifndef _BULLET_H__
#define _BULLET_H__

#include"Entity.h"

class Bullet : public Entity {
public:
	
	CREATE_FUNC(Bullet);
	virtual bool init();
public:
	void MovebyLine();//子弹沿线移动
	void Fade();//碰壁打人消失
private:
	bool isNeedFade;//判断是否需要消失
};
#endif // !_BULLET_H__


