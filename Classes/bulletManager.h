#pragma once
#include <cocos2d.h>
USING_NS_CC;
class bulletManager:public Node
{
public:
	bool init();
	
	Vector<Node*> b_e_vec;
	Vector<Node*> b_e_vec_wait;

	Vector<Node*> b_p_vec;
	Vector<Node*> b_p_vec_wait;

	void update(float dt);

	static bulletManager* getIns();
private:
	CREATE_FUNC(bulletManager);
};

