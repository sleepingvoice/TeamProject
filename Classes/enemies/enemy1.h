#pragma once
#include <cocos2d.h>
USING_NS_CC;

//������ y ��ġ���� ���� �������� �� ���� ���ʹ�

class enemy1 :public Node
{
public:
	bool init();
	CREATE_FUNC(enemy1);

	void enemy1_Active(), enemy1_DisAct();
	Rect getBox();
};

