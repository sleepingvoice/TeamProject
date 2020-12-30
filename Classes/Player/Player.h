#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Player:public Node
{
public:
	bool init();
	CREATE_FUNC(Player);

	int hp;
	bool isDamage;//�� ��ü�� �浹����Ȯ�κ���

	void player_Act();
	void player_DisAct();

	//�÷��̾� ��ü�� ������ ����
	void Press(EventKeyboard::KeyCode key, Event* e);
	void Release(EventKeyboard::KeyCode key, Event* e);
	void update(float dt);
	bool up, down, right, left;

	//�÷��̾� ��ü�� hitBox
	Rect getBox();

	//�÷��̾� �浹�Լ�
	void damage();

	static Player* getIns();
};

