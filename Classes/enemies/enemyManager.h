#pragma once
#include <cocos2d.h>
USING_NS_CC;

#include "enemies/enemy1.h"
#include "enemies/enemy2.h"
#include "enemies/eBullet.h"

class enemyManager:public Layer
{
public:
	bool init();

	//���ʹ�1 ����
	Vector<enemy1*> e1_vec; //���� ȭ�鿡�� ������� ��ü�� �����ϴ� ����
	Vector<enemy1*> e1_vec_wait; //���� ����ϱ� ���� ��ü�� �����ϴ� ����

	//���ʹ�2 ����
	Vector<enemy2*> e2_vec;
	Vector<enemy2*> e2_vec_wait;

	void update(float dt), eM_DisAct();

	float e1_timer, e2_timer; //���ʹ�1,2 ���� Ÿ�̸�
	
	int e2_y; //���ʹ�2 y�� ���ϴ� int

	static enemyManager* getIns();

private:
	CREATE_FUNC(enemyManager);
};

