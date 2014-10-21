#define WINSIZE Director::getInstance()->getWinSize()

#include "Negi.h"

NegiSprite::NegiSprite()
{
}

NegiSprite::~NegiSprite()
{
    this->removeAllChildren();
    log("解放:NegiSprite");
}

bool NegiSprite::init()
{
    if (!Sprite::initWithFile("negi.png"))
    {
        return false;
    }
    
    setSprite();
    
    return true;
}

void NegiSprite::setSprite()
{
    Size visibleSize = WINSIZE;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    
    float setLine = 3.0;
    
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setFloatForKey("SetLine", setLine);
    userDef->flush();
}
