#ifndef __RESULT_TEXT__
#define __RESULT_TEXT__

#include "cocos2d.h"

USING_NS_CC;

class resultText : public cocos2d::Layer
{
private:
    std::vector<std::string> arrayText;
    int score;
    
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Button,
        Z_Label,
    };
    
public:
    resultText();
    virtual ~resultText();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void initSetBackGround();
    void initSetButton();

    void textSelect();
    void texts(int textRoot);
    void displayText();
    
    virtual void spriteConfig();
    virtual void reStart();
    virtual void gameEnd(cocos2d::Ref* pSender);

    CREATE_FUNC(resultText);
};

#endif /* defined(__BackCoverCut__ResultText__) */
