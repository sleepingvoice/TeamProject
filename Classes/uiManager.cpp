#include "uiManager.h"
#include "ui/Ui_hpicon.h"
#include "ui/Ui_Score.h"

bool uiManager::init()
{
    Ui_hpicon* hp = Ui_hpicon::getIns();
    this->addChild(hp);
    Ui_Score* score = Ui_Score::getIns();
    this->addChild(score);

    return true;
}
