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
	float numx; float numy; int S;//ͨ����������ȷ���켣
	int Bullet_accuracy=7;//�ӵ�׼��

	bool isNeedFade= false;//�ж��Ƿ���Ҫ��ʧ
};
#endif // !_BULLET_H__


