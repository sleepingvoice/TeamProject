#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Player:public Node
{
public:


	int hp;
	int speed;
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

	void reset();

	static Player* getIns();

	void mouseDown(EventMouse* e);

private:
	bool init();
	CREATE_FUNC(Player);	
};

