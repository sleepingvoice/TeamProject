#pragma once
#include <cocos2d.h>
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

class soundManager:public Layer
{
public:
	bool init(), mute = false;

	static soundManager* getIns();

	int bgm_tag = 0;
	float sfx_vol = 1, bgm_vol = 1;

	void btnClk(Ref* ref, CheckBox::EventType type), sliderMove1(Ref* ref, Slider::EventType type), sliderMove2(Ref* ref, Slider::EventType type), chkBt(Ref* ref, CheckBox::EventType type), bgm(int i), sfx(int i), stopA();

private:
	CREATE_FUNC(soundManager);
};

