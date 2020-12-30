#include "enemy2.h"

bool enemy2::init()
{
    /*������1 1000, 600
    ������2 1000, 440
    ������3 1000, 280
    ������4 1000, 120*/

    Sprite* en2 = Sprite::create("enemy2.png");
    this->addChild(en2);
    en2->setName("en2");
    this->setPosition(Vec2(9999, 999));

    return true;
}

void enemy2::enemy2_Active(int y)
//���ʹ� Ȱ��ȭ �Լ�
{
    this->setPosition(Vec2(1325, 600 - 160 * y));
    /*y�� 0 = 600
    y�� 1 = 440
    y�� 2 = 280
    y�� 3 = 120*/

    MoveBy* mby1 = MoveBy::create(1, Vec2(-325, 0));
    DelayTime* dt = DelayTime::create(10);
    MoveBy* mby2 = MoveBy::create(2, Vec2(0, 800));

    Sequence* seq = Sequence::create(mby1, dt, mby2, 0);

    this->setVisible(true);
    this->runAction(seq);
}

void enemy2::enemy2_DisAct()
//���ʹ� ��Ȱ��ȭ �Լ�
{
    this->stopAllActions();
    this->setVisible(false);
}

void enemy2::damage()
{
    this->setPositionY(785);
}

Rect enemy2::getBox()
{
    Sprite* en2 = (Sprite*)this->getChildByName("en2");
    Rect rt = en2->getBoundingBox();
    rt.origin += this->getPosition();

    return rt;
}
