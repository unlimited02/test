#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Title : public cocos2d::Layer
{
private:
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Button,
        Z_Label,
    };

public:
    Title();
    virtual ~Title();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void setBackGround();
    void setButton();
    
    virtual void menuStart();
    virtual void menuEnd(cocos2d::Ref* pSender);
    virtual void menuConfig();
    
    CREATE_FUNC(Title);
};

#endif /* __TITLE_SCENE_H__ */
