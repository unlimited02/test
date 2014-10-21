#ifndef __BackCoverCut__BookSprite__
#define __BackCoverCut__BookSprite__

#include "cocos2d.h"

USING_NS_CC;

class BookSprite : public Sprite
{
public:
    BookSprite();
    virtual ~BookSprite();
    
    virtual bool init();
    
    void setSprite();
    
    CREATE_FUNC(BookSprite);
};

#endif /* defined(__BackCoverCut__BookSprite__) */
