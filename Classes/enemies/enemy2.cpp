#include "enemy2.h"
#include "../enemies/enemyManager.h"
#include "../bulletManager.h"

bool enemy2::init()
{
    /*������1 1000, 600
    ������2 1000, 440
    ������3 1000, 280
    ������4 1000, 120*/

    hp = 0;
    spawn_eb = 0;
    hit = false;

    Sprite* en2 = Sprite::create("enemy2.png");
    this->addChild(en2);
    en2->setName("en2");
    this->setPosition(Vec2(9999, 999));

    return true;
}

void enemy2::update(float dt)
{
    if (this->getPositionY() >= 670)
    {
        this->unscheduleUpdate();
    }
    else if (this->getPositionX() <= 1235)
    {
        //���ʹ� �ҷ� ����
        spawn_eb += dt;
        if (spawn_eb >= 1)
        {
            spawn_eb -= 1;

            if ((eBullet*)bulletManager::getIns()->b_e_vec_wait.size() > 0)
            {
                eBullet* e = (eBullet*)bulletManager::getIns()->b_e_vec_wait.back();
                bulletManager::getIns()->b_e_vec.pushBack(e);
                bulletManager::getIns()->b_e_vec_wait.eraseObject(e);
                e->eb_Active(this->getPosition());
                return;
            }
            else
            {
                eBullet* e = eBullet::create();
                this->getParent()->addChild(e);
                e->setZOrder(3);
                bulletManager::getIns()->b_e_vec.pushBack(e);
                e->eb_Active(this->getPosition());
            }
        }
    }
}

void enemy2::enemy2_Active(int y)
//���ʹ� Ȱ��ȭ �Լ�
{
    hp = 3;

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

    this->scheduleUpdate();
}

void enemy2::enemy2_DisAct()
//���ʹ� ��Ȱ��ȭ �Լ�
{
    this->stopAllActions();
    this->unscheduleUpdate();
    spawn_eb = 0;
    this->setVisible(false);
}

void enemy2::damage()
{
    if (hit == false)
    {
        hp--;
        if (hp <= 0)
        {
            this->setPositionY(785);
        }
        else
        {
            hit = true;

            Blink* b = Blink::create(0.5f, 1);
            CallFunc* cf = CallFunc::create(CC_CALLBACK_0(enemy2::invic, this));
            Sequence* seq = Sequence::create(b, cf, 0);

            Sprite* en2 = (Sprite*)this->getChildByName("en2");
            en2->runAction(seq);
        }
    }
}

void enemy2::invic()
{
    hit = false;
}

Rect enemy2::getBox()
{
    Sprite* en2 = (Sprite*)this->getChildByName("en2");
    Rect rt = en2->getBoundingBox();
    rt.origin += this->getPosition();

    return rt;
}
