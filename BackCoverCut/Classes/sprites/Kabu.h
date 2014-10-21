#ifndef __BackCoverCut__Kabu__
#define __BackCoverCut__Kabu__

#include "cocos2d.h"

USING_NS_CC;

class KabuSprite : public Sprite
{
public:
    KabuSprite();
    virtual ~KabuSprite();
    
    virtual bool init();
    
    void setSprite();
    
    CREATE_FUNC(KabuSprite);
};

#endif /* defined(__BackCoverCut__Kabu__) */
