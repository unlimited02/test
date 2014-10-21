#define DEFAULT_BLADEPOS_X 550
#define DEFAULT_BLADEPOS_Y 500

#include "Blade.h"

BladeSprite::BladeSprite()
{
}

BladeSprite::~BladeSprite()
{
    this->removeAllChildren();
    log("解放:BladeSprite");
}

bool BladeSprite::init()
{
    if (!Sprite::initWithFile("brade.png"))
    {
        return false;
    }
    
    setSprite();
    
    return true;
}

void BladeSprite::setSprite()
{
    this->setPosition(Vec2(DEFAULT_BLADEPOS_X, DEFAULT_BLADEPOS_Y));
    this->setScale(0.3);
    this->setScaleY(0.2);
    this->setRotation(70);
}
