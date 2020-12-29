#include "enemy2.h"

bool enemy2::init()
{
    /*포지션1 1000, 600
    포지션2 1000, 440
    포지션3 1000, 280
    포지션4 1000, 120*/

    Sprite* e1 = Sprite::create("enemy2.png");
    this->addChild(e1);
    this->setPosition(Vec2(9999, 999));

    return true;
}

void enemy2::enemy2_Active(int y)
//에너미 활성화 함수
{
    this->setPosition(Vec2(1325, 600 - 160 * y));
    /*y가 0 = 120
    y가 1 = 280
    y가 2 = 440
    y가 3 = 600*/

    MoveBy* mby1 = MoveBy::create(1, Vec2(-325, 0));
    DelayTime* dt = DelayTime::create(10);
    MoveBy* mby2 = MoveBy::create(2, Vec2(0, 800));

    Sequence* seq = Sequence::create(mby1, dt, mby2, 0);

    this->setVisible(true);
    this->runAction(seq);
}

void enemy2::enemy2_DisAct()
//에너미 비활성화 함수
{
    this->stopAllActions();
    this->setVisible(false);
}