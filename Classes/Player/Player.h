#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Player:public Node
{
public:
	bool init();
	CREATE_FUNC(Player);

	int hp;
	int Speed;

	//�÷��̾� ��ü�� ������ ����
	void Press(EventKeyboard::KeyCode key, Event* e);
	void Release(EventKeyboard::KeyCode key, Event* e);
	void update(float dt);
	bool up, down, right, left;

	//�÷��̾� ��ü�� hitBox
	Rect getBox();

	static Player* getIns();
};

