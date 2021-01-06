#include "Ui_Score.h"

static Ui_Score* obj = 0;

bool Ui_Score::init()
{
    finalScore = 0;

    Label* score = Label::createWithTTF("00000", "fonts/Recipekorea_FONT.ttf", 50);
    this->addChild(score);
    score->setPosition(Vec2(1260, 670));
    score->setAnchorPoint(Vec2(1, 0.5));
    score->setName("score");

    return true;
}

void Ui_Score::scoreUp(int score)
{
    Label* s = (Label*)this->getChildByName("score");
    finalScore += score;
    std::string str = StringUtils::format("%05d", finalScore);
    s->setString(str);
}

void Ui_Score::reset()
{
    finalScore = 0;

    Label* s = (Label*)this->getChildByName("score");
    std::string str = StringUtils::format("00000");
    s->setString(str);
}

Ui_Score* Ui_Score::getIns()
{
    if (obj == 0) {
        obj = Ui_Score::create();
        obj->retain();
    }
    return obj;
}
