#include "Boss.h"
#include "laser/laser1.h"
#include "bulletManager.h"
#include "enemies/eBullet.h"
#include "Scene/s_ClearScene.h"

bool Boss::init()
{
    Sprite* Boss = Sprite::create("Boss.png");
    this->addChild(Boss);
    Boss->setTag(1);
    Boss->setPositionY(-50);
    Boss->setScale(2);
    Boss->setName("Boss");

    target = Vec2(1000, 200);
    dir = Vec2(-1, 1);

    MoveBy* m1 = MoveBy::create(2, Vec2(-300,0));
    this->runAction(m1);

    Next = false;
    Die = false;
    particle = false;
    speed = 100;

    this->scheduleUpdate();

    Hp = 10;
    return true;
}

Rect Boss::GetBox()
{
    Sprite* pSpr = (Sprite*)this->getChildByName("Boss");
    if (pSpr != NULL) {
        Rect rt = pSpr->getBoundingBox();
        rt.origin += this->getPosition();
        return rt;
    }
}

void Boss::Damage()
{
    Hp--;
    if (Hp == 5)
    {
        change();
    }
    if (Hp <= 0)
    {
        Die = true;
    }
}

void Boss::update(float dt)
{
    Time += dt;
    
    if(Time >= 2.5f && Die != true)
    {
        speed += dt * 80;
        this->setPosition(this->getPosition() + dir * dt * speed);
        if (this->getPositionX() < 600) {
            dir += Vec2(2, 0);
        }
        if (this->getPositionX() > 1150)
        {
            dir += Vec2(-2, 0);
        }
        if (this->getPositionY() > 650)
        {
            dir += Vec2(0, -2);
        }
        if (this->getPositionY() < 150)
        {
            dir += Vec2(0, 2);
        }
        dirMax();
    }

    if (Die == true) {
        DeadTime += dt;
        if (particle == false) {
            ParticleSystem* par;
            par = ParticleExplosion::create();
            DelayTime* d = DelayTime::create(5);
            RemoveSelf* r = RemoveSelf::create(true);
            Sequence* seq = Sequence::create(d, r, 0);
            this->addChild(par);
            par->runAction(seq);
            par->setPosition(this->getChildByTag(1)->getPosition());
            particle = true;
            shotTime = -9999;
        }

        if(DeadTime > 5)
        {
            s_ClearScene* sc = s_ClearScene::create();
            Director::getInstance()->replaceScene(sc);
            this->removeFromParentAndCleanup(true);
        }
    }
    shotTime += dt;
    if (shotTime >= 2)
    {
        now_speed = speed;
        shotTime -= 2;
        pattern_1();
        speed=0;
    }
    if (shotTime == 0.5f)
    {
        speed = now_speed;
    }
}

void Boss::change()
{
    Sprite* pSpr = (Sprite*)this->getChildByTag(1);
    pSpr->setTexture("Boss_2.png");
    Next = true;
    Time = 1;
    shotTime = 0;
    dir = Vec2(-1, -1);
    speed = speed * 2;
}

void Boss::dirMax()
{
    if (dir.x > 1)
    {
        dir.x = 1;
    }
    else if (dir.x < -1)
    {
        dir.x = -1;
    }
    if (dir.y > 1)
    {
        dir.y = 1;
    }
    else if (dir.y < -1)
    {
        dir.y = -1;
    }
}

void Boss::pattern_1()
{
    
    for (float i = -0.5f; i < 2; i=i+0.5f) {
        if ((eBullet*)bulletManager::getIns()->b_e_vec_wait.size() > 0)
        {
            eBullet* e = (eBullet*)bulletManager::getIns()->b_e_vec_wait.back();
            bulletManager::getIns()->b_e_vec.pushBack(e);
            bulletManager::getIns()->b_e_vec_wait.eraseObject(e);
            e->eb_Active(this->getPosition());
            e->dir = Vec2(1, i);
        }
        else
        {
            eBullet* e = eBullet::create();
            this->getParent()->addChild(e);
            bulletManager::getIns()->b_e_vec.pushBack(e);
            e->eb_Active(this->getPosition());
            e->dir = Vec2(1, i);
        }
    }
}

void Boss::pattern_2()
{
}


