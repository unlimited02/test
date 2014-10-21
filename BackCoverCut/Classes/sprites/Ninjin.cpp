#define WINSIZE Director::getInstance()->getWinSize()

#include "Ninjin.h"

NinjinSprite::NinjinSprite()
{
}

NinjinSprite::~NinjinSprite()
{
    this->removeAllChildren();
    log("解放:NinjinSprite");
}

bool NinjinSprite::init()
{
    if (!Sprite::initWithFile("ninjin.png")) {
        return false;
    }
    
    setSprite();
    
    return true;
}

void NinjinSprite::setSprite()
{
    Size visibleSize = WINSIZE;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    
    float setLine = 3.0;
    
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setFloatForKey("SetLine", setLine);
    userDef->flush();
}
