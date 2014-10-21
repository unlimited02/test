#ifndef __BackCoverCut__DescriptionScene__
#define __BackCoverCut__DescriptionScene__

#include "cocos2d.h"

USING_NS_CC;

class Description : public Layer
{
private:
    int count = 0;
    
    enum ZOrder
    {
        Z_Sprite = 0,
        Z_Button,
        Z_Label,
    };
    
    enum Tag
    {
        T_Sprite1 = 0,
        T_Sprite2 = 1,
        T_Sprite3 = 2,
    };
    
public:
    Description();
    virtual ~Description();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void setSprite();
    void setButton();
    void setLabel();
    void gameStart();
    
    static FiniteTimeAction *action1();
    static FiniteTimeAction *action2();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    CREATE_FUNC(Description);
};

#endif /* defined(__BackCoverCut__DescriptionScene__) */
