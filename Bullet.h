#ifndef _BULLET_H__
#define _BULLET_H__

#include"Entity.h"

class Bullet : public Entity {
public:
	
	CREATE_FUNC(Bullet);
	virtual bool init();
public:
	void MovebyLine();//�ӵ������ƶ�
	void Fade();//���ڴ�����ʧ
private:
	bool isNeedFade;//�ж��Ƿ���Ҫ��ʧ
};
#endif // !_BULLET_H__


