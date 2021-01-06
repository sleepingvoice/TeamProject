#include "soundManager.h"
#include <AudioEngine.h>
using namespace experimental;

static soundManager* obj = 0;

bool soundManager::init()
{
    Sprite* bk = Sprite::create("Setting/panel.png");
    this->addChild(bk);
    bk->setPosition(Vec2(640, 360));
    bk->setTag(1);
    bk->setVisible(false);

    Slider* sl1 = Slider::create("Setting/grey_sliderHorizontal.png", "Setting/grey_sliderDown.png");
    this->addChild(sl1);
    sl1->setPosition(Vec2(670, 420));
    sl1->setPercent(100);
    sl1->addEventListener(CC_CALLBACK_2(soundManager::sliderMove1, this));
    sl1->setZOrder(11);
    sl1->setTag(2);
    sl1->setVisible(false);

    Label* lb1 = Label::createWithTTF("BGM", "fonts/Recipekorea_FONT.ttf", 20);
    this->addChild(lb1);
    lb1->setColor(Color3B::BLACK);
    lb1->setPosition(Vec2(525, 420));
    lb1->setZOrder(11);
    lb1->setTag(3);
    lb1->setVisible(false);

    Slider* sl2 = Slider::create("Setting/grey_sliderHorizontal.png", "Setting/grey_sliderDown.png");
    this->addChild(sl2);
    sl2->setPosition(Vec2(670, 360));
    sl2->setPercent(100);
    sl2->addEventListener(CC_CALLBACK_2(soundManager::sliderMove2, this));
    sl2->setZOrder(11);
    sl2->setTag(4);
    sl2->setVisible(false);

    Label* lb2 = Label::createWithTTF("SFX", "fonts/Recipekorea_FONT.ttf", 20);
    this->addChild(lb2);
    lb2->setColor(Color3B::BLACK);
    lb2->setPosition(Vec2(523, 360));
    lb2->setZOrder(11);
    lb2->setTag(5);
    lb2->setVisible(false);

    Label* lb3 = Label::createWithTTF("MUTE", "fonts/Recipekorea_FONT.ttf", 20);
    this->addChild(lb3);
    lb3->setColor(Color3B::BLACK);
    lb3->setPosition(Vec2(525, 300));
    lb3->setZOrder(11);
    lb3->setTag(6);
    lb3->setVisible(false);

    CheckBox* cb = CheckBox::create("Setting/grey_box.png", "Setting/grey_boxCheckmark.png");
    this->addChild(cb);
    cb->setPosition(Vec2(590, 302));
    cb->addEventListener(CC_CALLBACK_2(soundManager::chkBt, this));
    cb->setZOrder(11);
    cb->setTag(7);
    cb->setVisible(false);

    CheckBox* bt = CheckBox::create("Setting/gear.png", "Setting/cross.png");
    this->addChild(bt);
    bt->setPosition(Vec2(1250, 690));
    bt->setZOrder(10);
    bt->addEventListener(CC_CALLBACK_2(soundManager::btnClk, this));

    return true;
}

void soundManager::btnClk(Ref* ref, CheckBox::EventType type)
{
    CheckBox* box = (CheckBox*)ref;
    bool b = box->getSelectedState();

    if (b == true)
    {
        for (int i = 1; i <= 7; i++)
        {
            Node* n = (Node*)this->getChildByTag(i);
            n->setVisible(true);
        }
    }
    else if (b == false)
    {
        for (int i = 1; i <= 7; i++)
        {
            Node* n = (Node*)this->getChildByTag(i);
            n->setVisible(false);
        }
    }
}

void soundManager::sliderMove1(Ref* ref, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* sld = (Slider*)ref;

        AudioEngine::setVolume(bgm_tag, sld->getPercent() * 0.01f);
    }
}

void soundManager::sliderMove2(Ref* ref, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* sld = (Slider*)ref;

        sfx_vol = sld->getPercent() * 0.01f;
    }
}

void soundManager::chkBt(Ref* ref, CheckBox::EventType type)
{
    CheckBox* box = (CheckBox*)ref;
    bool b = box->getSelectedState();

    if (b == true)
    {
        AudioEngine::pause(bgm_tag);
        mute = true;
    }
    else if (b == false)
    {
        AudioEngine::resume(bgm_tag);
        mute = false;
    }
}

void soundManager::bgm(int i)
{
    if (mute == false)
    {
        switch (i)
        {
        case 0:
            bgm_tag = AudioEngine::play2d("BGM/EnemiesBattle.mp3", true, bgm_vol);
            break;
        case 1:
            AudioEngine::stop(bgm_tag);
            bgm_tag = AudioEngine::play2d("BGM/BossBattle.mp3", true, bgm_vol);
            break;
        case 2:
            AudioEngine::stop(bgm_tag);
            AudioEngine::play2d("BGM/Clear.mp3", false, bgm_vol);
            break;
        case 3:
            AudioEngine::stop(bgm_tag);
            AudioEngine::play2d("BGM/GameOver.mp3", false, bgm_vol);
            break;
        }
    }
    else if (mute == true && i == 2)
    {
        AudioEngine::stop(bgm_tag);
        bgm_tag = AudioEngine::play2d("BGM/BossBattle.mp3", true, bgm_vol);
        AudioEngine::pause(bgm_tag);
    }
}

void soundManager::sfx(int i)
{
    if (mute == false)
    {
        switch (i)
        {
        case 0:
            AudioEngine::play2d("SFX/EnemyHit.mp3", false, sfx_vol);
            break;
        case 1:
            AudioEngine::play2d("SFX/EnemyDie.mp3", false, sfx_vol);
            break;
        case 2:
            AudioEngine::play2d("SFX/Player/LaserShoot.mp3", false, sfx_vol);
            break;
        case 3:
            AudioEngine::play2d("SFX/Player/LootTem.mp3", false, sfx_vol);
            break;
        case 4:
            AudioEngine::play2d("SFX/Player/Male/m_Hit.mp3", false, sfx_vol);
            break;
        case 5:
            AudioEngine::play2d("SFX/Player/Male/m_Die.mp3", false, sfx_vol);
            break;
        case 6:
            AudioEngine::play2d("SFX/Player/Male/m_Start.mp3", false, sfx_vol);
            break;
        }
    }
}

void soundManager::stopA()
{
    AudioEngine::stopAll();
}

soundManager* soundManager::getIns()
{
    if (obj == 0)
    {
        obj = soundManager::create();
    }
    return obj;
}
