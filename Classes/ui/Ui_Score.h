#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Ui_Score:public Layer
{
public:
	bool init();

	int finalScore;
	void scoreUp(int score);

	CREATE_FUNC(Ui_Score);
	
	static Ui_Score* getIns();
};

