#pragma once
#include <cocos2d.h>
USING_NS_CC;
class player_shoot:public Layer
{
public:
	bool init();
	CREATE_FUNC(player_shoot);

	void mouseDown(EventMouse* e);
	void mouseUp(EventMouse* e);

	static player_shoot* getIns();
};
