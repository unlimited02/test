#ifndef __BackCoverCut__negiSprite__
#define __BackCoverCut__negiSprite__

#include "cocos2d.h"

USING_NS_CC;

class NegiSprite : public Sprite
{
public:
    NegiSprite();
    virtual ~NegiSprite();
    
    virtual bool init();
    
    void setSprite();
    
    CREATE_FUNC(NegiSprite);
};

#endif /* defined(__BackCoverCut__negiSprite__) */
