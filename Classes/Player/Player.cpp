#include "Player.h"
#include "player_shoot.h"
#include "../Scene/s_GameoverScene.h"

static Player* obj = 0;

bool Player::init()
{
	isDamage = true;
	hp = 3;
	speed = 350;
	left = false;
	right = false;
	up = false;
	down = false;

    Sprite* player = Sprite::create("playertest.png");
    player->setPosition(Vec2(100, 360));
    this->addChild(player);
    player->setName("player");

	player_shoot* shoot = player_shoot::getIns();
	this->addChild(shoot);

	EventListenerKeyboard* km = EventListenerKeyboard::create();
	km->onKeyPressed = CC_CALLBACK_2(Player::Press, this);
	km->onKeyReleased = CC_CALLBACK_2(Player::Release, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(km, this);

	this->scheduleUpdate();

    return true;
}

void Player::player_Act()
{
	isDamage = true;
}

void Player::player_DisAct()
{
	isDamage = false;
}

void Player::Press(EventKeyboard::KeyCode key, Event* e)
{
	if (key == EventKeyboard::KeyCode::KEY_A) {
		left = true;
	}
	else if (key == EventKeyboard::KeyCode::KEY_D) {
		right = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_W) {
		up = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_S) {
		down = true;
	}
}

void Player::Release(EventKeyboard::KeyCode key, Event* e)
{
	if (key == EventKeyboard::KeyCode::KEY_A) {
		left = false;
	}
	else if (key == EventKeyboard::KeyCode::KEY_D) {
		right = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_W) {
		up = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_S) {
		down = false;
	}
}

void Player::update(float dt)
{
	Sprite* p = (Sprite*)this->getChildByName("player");
	if (left == true)
		p->setPositionX(p->getPositionX() - speed * dt);
	else if (right == true)
		p->setPositionX(p->getPositionX() + speed * dt);
	if (down == true)
		p->setPositionY(p->getPositionY() - speed * dt);
	if (up == true)
		p->setPositionY(p->getPositionY() + speed * dt);
}

Rect Player::getBox()
{//�浹 �ڽ� ����
	Sprite* p = (Sprite*)this->getChildByName("player");
	Rect rt = p->getBoundingBox();
	rt.origin += this->getPosition();
	return rt;
}

void Player::damage()
{
	if (hp > 0 && isDamage == true) {
		hp--;

		//�浹 �� ��¦�� ȿ���� ��
		Sprite* p = (Sprite*)this->getChildByName("player");
		Blink* bnk = Blink::create(3, 6);

		CallFunc* dis = CallFunc::create(CC_CALLBACK_0(Player::player_DisAct, this));
		CallFunc* act = CallFunc::create(CC_CALLBACK_0(Player::player_Act, this));

		Sequence* seq = Sequence::create(dis, bnk, act, 0);
		p->runAction(seq);
	}
	else if (hp <= 0) {
		s_GameoverScene* sc = s_GameoverScene::create();
		Director::getInstance()->replaceScene(sc);
	}
}

void Player::reset()
{
	Sprite* p = (Sprite*)this->getChildByName("player");
	p->setVisible(true);

	isDamage = true;
	hp = 3;
	speed = 350;
	left = false;
	right = false;
	up = false;
	down = false;
	p->setPosition(Vec2(100, 360));

	this->scheduleUpdate();
}

Player* Player::getIns()
{
	if (obj == 0) {
		obj = Player::create();
		obj->retain();
	}
	return obj;
}

