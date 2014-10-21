#ifndef __BackCoverCut__Blade__
#define __BackCoverCut__Blade__

#include "cocos2d.h"

USING_NS_CC;

class BladeSprite : public Sprite
{
public:
    BladeSprite();
    virtual ~BladeSprite();
    
    virtual bool init();
    
    void setSprite();
    
    CREATE_FUNC(BladeSprite);
};

#endif /* defined(__BackCoverCut__Blade__) */
