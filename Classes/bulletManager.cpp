#include "bulletManager.h"
#include "enemies/eBullet.h"
#include "laser/laser1.h"

static bulletManager* obj = 0;

bool bulletManager::init()
{
    for (int i = 0; i < 10; i++)
    {
        eBullet* eb = eBullet::create();
        this->addChild(eb);
        b_e_vec_wait.pushBack((Node*)eb);
        eb->setZOrder(3);
    }

    this->scheduleUpdate();

	return true;
}

void bulletManager::update(float dt)
{
    for (Node* laser : b_p_vec)
    {
        laser1* l = (laser1*)laser;
        if (l->getPositionX() > 1300) {
            b_p_vec_wait.pushBack((Node*)l);
            b_p_vec.eraseObject(l);
            l->laser1_DisAct();
            return;
        }
    }
    //레이저 화면밖 처리
    for (Node* Bullet : b_e_vec)
    {
        eBullet* e = (eBullet*)Bullet;
        if (e->getPositionX() <= -35) {
            b_e_vec_wait.pushBack((Node*)e);
            b_e_vec.eraseObject(e);
            e->eb_DisAct();
            
            return;
            
        }
    }
    //불릿 화면밖 처리
}

bulletManager* bulletManager::getIns()
{
    if (obj == 0)
    {
        obj = bulletManager::create();
    }
    return obj;
}
