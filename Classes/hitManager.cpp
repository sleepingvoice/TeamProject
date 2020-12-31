#include "hitManager.h"
#include "Boss/Boss.h"
#include "laser/laser1.h"

static hitManager* obj = 0;

bool hitManager::init()
{
    this->scheduleUpdate();

	return true;
}


void hitManager::Playerenemy()
{
    if (em->e1_vec.empty() != true)
    {
        for (Node* p : em->e1_vec)
        {
            enemy1* e = (enemy1*)p;
            Rect r1 = play->getBox();
            Rect r2 = e->getBox();
            if (r1.intersectsRect(r2) == true)
            {
                play->damage();
                break;
            }
        }
    }
    if (em->e2_vec.empty() != true)
    {
        for (Node* p : em->e2_vec)
        {
            enemy2* e = (enemy2*)p;
            Rect r1 = play->getBox();
            Rect r2 = e->getBox();
            if (r1.intersectsRect(r2) == true)
            {
                play->damage();
                break;
            }
        }
    }
}

void hitManager::Playerboss()
{
    Node* parent = this->getParent();
    Boss* boss = (Boss*)parent->getChildByName("Boss");
    if (boss != NULL)
    {
        Rect r1 = play->getBox();
        Rect r2 = boss->GetBox();
        if (r1.intersectsRect(r2) == true)
        {
            play->damage();
        }
    }
}

void hitManager::PlayerBullet()
{
    if (bullet->b_e_vec.empty() != true)
    {
        for (Node* b : bullet->b_e_vec)
        {
            eBullet* bul = (eBullet*)b;
            Rect r1 = play->getBox();
            Rect r2 = bul->getBox();
            if (r1.intersectsRect(r2) == true)
            {
                play->damage();
                bul->damage();
                break;
            }
        }
    }
}

void hitManager::Enemylaser()
{
    if (bullet->b_p_vec.empty() != true)
    {
        for (Node* b : bullet->b_p_vec)
        {
            if (em->e1_vec.empty() != true)
            {
                for (Node* p : em->e1_vec)
                {
                    laser1* Pbul = (laser1*)b;
                    enemy1* e = (enemy1*)p;
                    Rect r1 = Pbul->getBox();
                    Rect r2 = e->getBox();
                    if (r1.intersectsRect(r2) == true)
                    {
                        Pbul->setPosition(Vec2(9999, 9999));
                        e->damage();
                    }
                }
            }
            if (em->e2_vec.empty() != true)
            {
                for (Node* p : em->e2_vec)
                {
                    laser1* Pbul = (laser1*)b;
                    enemy2* e = (enemy2*)p;
                    Rect r1 = Pbul->getBox();
                    Rect r2 = e->getBox();
                    if (r1.intersectsRect(r2) == true)
                    {
                        Pbul->setPosition(Vec2(9999, 9999));
                        e->damage();
                    }
                }
            }
        }
    }
}

void hitManager::Bosslaser()
{
    if (bullet->b_p_vec.empty() != true)
    {
        for (Node* b : bullet->b_p_vec)
        {
            laser1* Pbul = (laser1*)b;
            Boss* boss = (Boss*)this->getParent()->getChildByName("Boss");
            if (boss != NULL) {
                Rect r1 = Pbul->getBox();
                Rect r2 = boss->GetBox();
                if (r1.intersectsRect(r2) == true)
                {
                    boss->Damage();
                    Pbul->setPositionX(9999);
                }
            }
        }
    }

}


void hitManager::update(float dt)
{
    play = (Player*)this->getParent()->getChildByName("Player");
    if (play != NULL)
    {
        Playerboss();
        //플레이어와 보스의 충돌판정
        Playerenemy();
        //플레이어와 적의 충돌판정
        PlayerBullet();
        //플레이어와 적총알의 충돌판정
        Enemylaser();
        //적과 총알의 충돌판정
        Bosslaser();
        //보스와 총알의 충돌판정
    }
}




hitManager* hitManager::getIns()
{
    if (obj == 0)
    {
        obj = hitManager::create();
    }
    return obj;
}
