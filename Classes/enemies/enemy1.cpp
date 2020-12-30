#include "enemy1.h"
#include "Player/Player.h"

bool enemy1::init()
{
    Sprite* en1 = Sprite::create("enemy1.png");
    this->addChild(en1);
    en1->setName("en1");

    this->setPosition(Vec2(9999, 999));

    enemy1_DisAct();

    return true;
}

void enemy1::update(float dt)
{
    if (this->getPositionX() <= 1248 && target == false)
    {
        dir = Player::getIns()->getChildByName("player")->getPosition() - this->getPosition();
        target = true;
    }

    if (target == true)
    {
        this->setPosition(this->getPosition() + dir.getNormalized() * dt * 600);
    }
    else
    {
        this->setPositionX(this->getPositionX() - dt * 600);
    }
}

void enemy1::enemy1_Active()
//에너미 활성화 함수
{
    target = false;

    int ranY = rand() % 671 + 25;
    this->setPosition(Vec2(1315, ranY));

    this->setVisible(true);

    this->scheduleUpdate();
}

void enemy1::enemy1_DisAct()
//에너미 비활성화 함수
{
    this->setVisible(false);
    this->unscheduleUpdate();
}

void enemy1::damage()
//에너미 데미지 받았을 때 처리
{
    this->setPositionX(-65);
}

Rect enemy1::getBox()
//충돌 박스 보정 함수
{
    Sprite* en1 = (Sprite*)this->getChildByName("en1");
    Rect rt = en1->getBoundingBox();
    rt.origin += this->getPosition();

    return rt;
}
