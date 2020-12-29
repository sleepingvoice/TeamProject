#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Boss :public Node
{
public:
	bool init();
	CREATE_FUNC(Boss);

	int Hp;
	float Time = 0;
	float shotTime = -1;
	Vec2 dir;
	Vec2 target;
	bool Next;
	bool Die;
	bool particle;
	float DeadTime = 0;


	Rect GetBox();
	void Damage();
	void update(float dt);
	void change();
	void pattern1();
	void pattern2();
	void dirMax();
};

