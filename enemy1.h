#pragma once
#include <cocos2d.h>
USING_NS_CC;

//������ y ��ġ���� ���� �������� �� ���� ���ʹ�

class enemy1:public Node
{
public:
	bool init(), target = false;
	CREATE_FUNC(enemy1);

	void update(float dt), enemy1_Active(), enemy1_DisAct(), damage();
	Rect getBox();

	Vec2 dir;

	float ang = 0;
};

