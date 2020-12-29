#include "Boss.h"
#include "m_bullet.h"

bool Boss::init()
{
    Sprite* Boss = Sprite::create("Boss1.png");
    this->addChild(Boss);
    Boss->setTag(1);
    Boss->setPositionY(-50);
    Boss->setScale(2);

    target = Vec2(1000, 200);
    dir = Vec2(-1, 1);

    MoveBy* m1 = MoveBy::create(2, Vec2(-300,0));
    this->runAction(m1);

    Next = false;
    Die = false;
    particle = false;

    this->scheduleUpdate();

    Hp = 10;
    return true;
}

Rect Boss::GetBox()
{
    Sprite* pSpr = (Sprite*)this->getChildByName("Boss");
    Rect rt = pSpr->getBoundingBox();
    rt.origin += this->getPosition();
    return rt;
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
        this->setPosition(this->getPosition() + dir * dt * 300);
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
    shotTime += dt;
    if (shotTime >= 1 && Die != true)
    {
        if (Next == false) 
        {
            pattern1();
        }
        else 
        {
            pattern2();
        }
        Damage();
        shotTime -= 1;
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
        }

        if(DeadTime > 5)
        {
            this->removeFromParentAndCleanup(true);
        }
    }
    
}

void Boss::change()
{
    Sprite* pSpr = (Sprite*)this->getChildByTag(1);
    pSpr->setTexture("Boss2.png");
    Next = true;
    Time = 1;
    shotTime = 0;
    dir = Vec2(-1, -1);
}

void Boss::pattern1()
{
    m_bullet* b1 = m_bullet::create();
    this->getParent()->addChild(b1);
    m_bullet* b2 = m_bullet::create();
    this->getParent()->addChild(b2);
    m_bullet* b3 = m_bullet::create();
    this->getParent()->addChild(b3);

    b1->dir = Vec2(-1, -0.5f);
    b2->dir = Vec2(-1, 0);
    b3->dir = Vec2(-1, 0.5f);

    b1->setPosition(this->getPosition() + Vec2(-10, 0));
    b2->setPosition(this->getPosition() + Vec2(-10, 0));
    b3->setPosition(this->getPosition() + Vec2(-10, 0));
}

void Boss::pattern2()
{
    m_bullet* b1 = m_bullet::create();
    this->getParent()->addChild(b1);
    b1->setPosition(this->getPosition() + Vec2(-10, 0));
    b1->dir = Vec2(-1, 0);
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
