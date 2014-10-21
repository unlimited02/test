#define WINSIZE Director::getInstance()->getWinSize()

#include "Book.h"

BookSprite::BookSprite()
{
}

BookSprite::~BookSprite()
{
    this->removeAllChildren();
    log("解放:BookSprite");
}

bool BookSprite::init()
{
    if (!Sprite::initWithFile("本.png"))
    {
        return false;
    }
    
    setSprite();
    
    return true;
}

void BookSprite::setSprite()
{
    Size visibleSize = WINSIZE;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->setPosition(Vec2(WINSIZE.width/1.4, WINSIZE.height/2));
    
    float setLine = 2.2;
    
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setFloatForKey("SetLine", setLine);
    userDef->flush();
}
