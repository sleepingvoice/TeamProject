#include "Player.h"
//#include "Ui_hpicon.h"
#include "player_shoot.h"

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
{//충돌 박스 보정
	Sprite* p = (Sprite*)this->getChildByName("player");
	Rect rt = p->getBoundingBox();
	rt.origin += this->getPosition();
	return rt;
}

void Player::damage()
{
	if (hp > 0 && isDamage == true) {
		hp--;

		//충돌 후 빤짝임 효과를 줌
		Sprite* p = (Sprite*)this->getChildByName("player");
		Blink* bnk = Blink::create(3, 6);
		DelayTime* dt = DelayTime::create(0.8);

		CallFunc* dis = CallFunc::create(CC_CALLBACK_0(Player::player_DisAct, this));
		CallFunc* act = CallFunc::create(CC_CALLBACK_0(Player::player_Act, this));

		Sequence* seq = Sequence::create(dis, bnk, dt, act, 0);
		p->runAction(seq);
	}
	else if (hp == 0) {
		//엔딩씬으로 교체
		//게임종료
	}
}

Player* Player::getIns()
{
	if (obj == 0) {
		obj = Player::create();
	}
	return obj;
}

