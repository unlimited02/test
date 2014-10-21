#ifndef __BackCoverCut__Ninjin__
#define __BackCoverCut__Ninjin__

#include "cocos2d.h"

USING_NS_CC;

class NinjinSprite : public Sprite
{
public:
    NinjinSprite();
    ~NinjinSprite();
    
    virtual bool init();
    
    void setSprite();
    
    CREATE_FUNC(NinjinSprite);
};

#endif /* defined(__BackCoverCut__Ninjin__) */
