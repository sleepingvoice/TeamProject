#include "player_shoot.h"
#include "bulletManager.h"
#include "laser/laser1.h"

static player_shoot* obj = NULL;

bool player_shoot::init()
{
    EventListenerMouse* em = EventListenerMouse::create();
    em->onMouseDown = CC_CALLBACK_1(player_shoot::mouseDown, this);
    em->onMouseUp = CC_CALLBACK_1(player_shoot::mouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(em, this);

    return true;
}

void player_shoot::mouseDown(EventMouse* e)
{
    EventMouse* em = (EventMouse*)e;
    if (em->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        if ((laser1*)bulletManager::getIns()->b_p_vec_wait.size() > 0) {
            laser1* p = (laser1*)bulletManager::getIns()->b_p_vec_wait.back();
            bulletManager::getIns()->b_p_vec.pushBack(p);
            bulletManager::getIns()->b_p_vec_wait.eraseObject(p);
            p->laser1_Active();
        }
        else {
            laser1* p = laser1::create();
            this->addChild(p);
            bulletManager::getIns()->b_p_vec.pushBack(p);
            p->laser1_Active();
            p->setZOrder(3);
        }
    }
    CCLOG("mouseDown");
}

void player_shoot::mouseUp(EventMouse* e)
{
    CCLOG("mouseUp");
}

player_shoot* player_shoot::getIns()
{
    if (obj == NULL)
        obj = player_shoot::create();
    return obj;
}
