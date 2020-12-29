#include "Player.h"

static Player* obj = 0;

bool Player::init()
{
	hp = 3;
	Speed = 350;
	left = false;
	right = false;
	up = false;
	down = false;

    Sprite* player = Sprite::create("playertest.png");
    player->setPosition(Vec2(100, 360));
    this->addChild(player);
    player->setName("player");

	EventListenerKeyboard* km = EventListenerKeyboard::create();
	km->onKeyPressed = CC_CALLBACK_2(Player::Press, this);
	km->onKeyReleased = CC_CALLBACK_2(Player::Release, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(km, this);

	this->scheduleUpdate();

    return true;
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
		p->setPositionX(p->getPositionX() - Speed * dt);
	else if (right == true)
		p->setPositionX(p->getPositionX() + Speed * dt);
	if (down == true)
		p->setPositionY(p->getPositionY() - Speed * dt);
	if (up == true)
		p->setPositionY(p->getPositionY() + Speed * dt);
}

Rect Player::getBox()
{//충돌 박스 보정
	Sprite* p = (Sprite*)this->getChildByName("player");
	Rect rt = p->getBoundingBox();
	rt.origin += this->getPosition();
	return rt;
}

Player* Player::getIns()
{
	if (obj == 0) {
		obj = Player::create();
	}
	return obj;
}

