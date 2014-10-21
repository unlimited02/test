#include "GameScene.h"
#include "DescriptionScene.h"

#define WINSIZE Director::getInstance()->getWinSize()

Description::Description()
{
}

Description::~Description()
{
    log("解放:Description");
    this->removeAllChildren();
}

Scene *Description::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer =  Description::create();
    scene->addChild(layer);
    
    return scene;
}

bool Description::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 画像の配置
    setSprite();
    
    // ボタンの配置
    setButton();
    
    // ラベルの配置
    setLabel();
    
    // タッチイベント
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Description::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Description::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// 画像の配置
void Description::setSprite()
{
    log("画像配置");
    
    Sprite *sample1 = Sprite::create("sample1.png");
    Sprite *sample2 = Sprite::create("sample2.png");
    Sprite *sample3 = Sprite::create("sample3.png");
    
    sample1->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    sample2->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    sample3->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    
    sample1->setScale(1.8);
    sample2->setScale(1.8);
    sample3->setScale(1.8);
    
    this->addChild(sample1, Z_Sprite, T_Sprite1);
    this->addChild(sample2, Z_Sprite, T_Sprite2);
    this->addChild(sample3, Z_Sprite, T_Sprite3);
    
    sample2->setOpacity(0);
    sample3->setOpacity(0);
}

// ボタンの配置
void Description::setButton()
{
    log("ボタン配置");
    
    // スキップボタン
    MenuItem *skipImage = MenuItemImage::create("skipBtn_default.png",
                                                "skipBtn_push.png",CC_CALLBACK_0(Description::gameStart, this));
    
    skipImage->setPosition(Vec2(WINSIZE.width/2 - WINSIZE.width/3,
                                WINSIZE.height/2 + WINSIZE.height/3));
    
    Menu *menu1 = Menu::create(skipImage,NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, Z_Button);
    
    Point skipPos = skipImage->getPosition();
    Label *skipLabel = Label::createWithSystemFont("スキップ", "ArialRoundedMTBold", 15);
    skipLabel->setPosition(skipPos.x, skipPos.y);
    this->addChild(skipLabel, Z_Label);
}

// ラベル配置
void Description::setLabel()
{
    log("ラベル配置");
    Label *helpLabel = Label::createWithSystemFont("画面を触ると刃が動くよ！\n目印にあわせて\nタイミングよく止めよう!!", "ArialRoundedMTBold", 30);
    helpLabel->setPosition(Vec2(WINSIZE.width/2 - WINSIZE.width/4,
                                WINSIZE.height/2 - WINSIZE.height/4));
    helpLabel->setColor(Color3B(190, 0, 120));
    this->addChild(helpLabel, Z_Label);
}

// 画像のアクション
FiniteTimeAction *Description::action1()
{
    ActionInterval *fadeIn = FadeIn::create(0.5);

    return fadeIn;
}

FiniteTimeAction *Description::action2()
{
    ActionInterval *fadeOut = FadeOut::create(0.5);
    
    return fadeOut;
}

// タッチアクション
bool Description::onTouchBegan(Touch *touch, Event *unused_event)
{
    log("タッチ開始");
    count++;
    
    switch (count) {
        case 1: getChildByTag(T_Sprite1)->runAction(Description::action2());
                getChildByTag(T_Sprite2)->runAction(Description::action1()); break;
        case 2: getChildByTag(T_Sprite2)->runAction(Description::action2());
                getChildByTag(T_Sprite3)->runAction(Description::action1()); break;
        case 3: gameStart(); break;
    }
    return true;
}

void Description::onTouchEnded(Touch *touch, Event *unused_event)
{
    log("タッチ終了");
}

// 画面遷移
void Description::gameStart()
{
    log("遷移:SpriteSetSccene");
    Scene *scene = Game::createScene();
    TransitionScene *effect = TransitionPageTurn::create(0.5, scene, 0);
    Director::getInstance()->replaceScene(effect);
}
