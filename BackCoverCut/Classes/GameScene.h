#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Game : public cocos2d::Layer
{
private:
    float distance;
    int tapCount = 0;
    int root;
    
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Sprite,
        Z_Blade,
        Z_Label,
        Z_Button,
    };
    
    enum Tag
    {
        T_Blade = 0,
        T_Book,
        T_Negi,
        T_Kabu,
        T_Ninjin,
    };
    
public:
    Game();
    virtual ~Game();

    static cocos2d::Scene* createScene();
    virtual bool init();
    void setSprite();
    void setBackGround();
    void setButton();
    void setBorder();
    
    static FiniteTimeAction* action1(float time);
    static FiniteTimeAction* action2(float time);
    static FiniteTimeAction* action3(float endPoint);
    static FiniteTimeAction* action4(float setBorder);
    static FiniteTimeAction* action5(float setBorder);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void scoreCalculate();
    float radianCalculation();
    float randomTime ();
    int randomCreate();

    virtual void reStart();
    virtual void endScene();
    
    CREATE_FUNC(Game);
};

#endif /* __GAME_SCENE_H__ */
