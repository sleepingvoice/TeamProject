#include "s_GameScene.h"
#include "Boss/m_Boss.h"
#include "Player/Player.h"
#include "enemies/enemyManager.h"
bool s_GameScene::init()
{
    m_Boss* boss=m_Boss::create();
    this->addChild(boss);
    boss->setPosition(1300, 200);

    Player* play = Player::create();
    this->addChild(play);
    play->setPosition(640, 360);

    enemyManager* em = enemyManager::getIns();
    this->addChild(em);


    return true;
}
