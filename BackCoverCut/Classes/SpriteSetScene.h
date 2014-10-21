#ifndef __BackCoverCut__SpriteSetScene__
#define __BackCoverCut__SpriteSetScene__

#include "cocos2d.h"

USING_NS_CC;

class SetSprite : public Layer
{
private:
    std::string currentSprite;
    int type = 0;
    
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Frame,
        Z_Button,
        Z_Label,
    };
    
    enum Tag
    {
        T_Frame1 = 0,
        T_Frame2,
        T_Rank1,
        T_Rank2,
        T_Rank3,
        T_Label,
    };
    
public:
    SetSprite();
    virtual ~SetSprite();
    static Scene* createScene();
    static void displayScore();
    
    virtual bool init();
    void setButton();
    void setBackGround();
    
    void setSpriteLabel();
    void setScoreLabel();
    void setNegi();
    void setBook();
    void setKabu();
    void setNinjin();
    void resetScore();

    virtual void ConfigEnd(cocos2d::Ref* pSender);
    
    CREATE_FUNC(SetSprite);
};

#endif /* defined(__BackCoverCut__SpriteSetScene__) */
