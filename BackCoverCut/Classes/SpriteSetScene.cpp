#include "TitleScene.h"
#include "SpriteSetScene.h"

#define WINSIZE Director::getInstance()->getWinSize()

SetSprite::SetSprite()
{
}

SetSprite::~SetSprite()
{
    this->removeAllChildren();
    log("解放:SetSprite");
}

Scene *SetSprite::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = SetSprite::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool SetSprite::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setIntegerForKey("Score", 0);
    currentSprite = userDef->getStringForKey("SpriteName");
    
    // 背景の配置
    setBackGround();
    
    // ボタンの配置
    setButton();

    // ハイスコア
    displayScore();
    
    // ハイスコアラベル
    setScoreLabel();
    
    // 表示する画像の名前
    setSpriteLabel();
    
    return true;
}

// 背景の配置
void SetSprite::setBackGround()
{
    Sprite *bg = Sprite::create("mokumeBG.png");
    bg->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    bg->setScale(1.2);
    this->addChild(bg, Z_Bg);
    
    Sprite *frame1 = Sprite::create("frame.png");
    frame1->setPosition(Vec2(WINSIZE.width/3, WINSIZE.height/2 + WINSIZE.height/3 - 75));
    frame1->setOpacity(120);
    frame1->setScale(0.9);
    this->addChild(frame1, Z_Frame, T_Frame1);
    
    Sprite *frame2 = Sprite::create("frame.png");
    frame2->setPosition(Vec2(WINSIZE.width/3, WINSIZE.height/3));
    frame2->setOpacity(120);
    frame2->setScale(0.9);
    this->addChild(frame2, Z_Frame, T_Frame2);
    log("背景設定");
}

// ボタンの配置
void SetSprite::setButton()
{
    
    // ネギボタン
    MenuItem *negiItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_0(SetSprite::setNegi, this));
    negiItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/2 + WINSIZE.height/3));

    Menu *menu1 = Menu::create(negiItem, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, Z_Button);
    
    Label *negiLabel = Label::createWithSystemFont("ネギ", "ArialRoundedMTBold", 30);
    negiLabel->setPosition(negiItem->getPosition());
    negiLabel->setScale(1.2);
    this->addChild(negiLabel, Z_Label);
    
    // 本ボタン
    MenuItem *bookItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_0(SetSprite::setBook, this));
    bookItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/2 + WINSIZE.height/3 - 50));

    Menu *menu2 = Menu::create(bookItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, Z_Button);
    
    Label *bookLabel = Label::createWithSystemFont("本", "ArialRoundedMTBold", 30);
    bookLabel->setPosition(bookItem->getPosition());
    bookLabel->setScale(1.2);
    this->addChild(bookLabel, Z_Label);
    
    // かぶボタン
    MenuItem *kabuItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_0(SetSprite::setKabu, this));
    kabuItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/2 + WINSIZE.height/3 - 100));
    
    Menu *menu3 = Menu::create(kabuItem, NULL);
    menu3->setPosition(Vec2::ZERO);
    this->addChild(menu3, Z_Button);
    
    Label *kabuLabel = Label::createWithSystemFont("かぶ", "ArialRoundedMTBold", 30);
    kabuLabel->setPosition(kabuItem->getPosition());
    kabuLabel->setScale(1.2);
    this->addChild(kabuLabel, Z_Label);
    
    // にんじんボタン
    MenuItem *ninjinItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_0(SetSprite::setNinjin, this));
    ninjinItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/2 + WINSIZE.height/3 -150));
    
    Menu *menu4 = Menu::create(ninjinItem, NULL);
    menu4->setPosition(Vec2::ZERO);
    
    this->addChild(menu4, Z_Button);
    
    Label *ninjinLabel = Label::createWithSystemFont("にんじん", "ArialRoundedMTBold", 30);
    ninjinLabel->setPosition(ninjinItem->getPosition());
    ninjinLabel->setScale(1.2);
    this->addChild(ninjinLabel, Z_Label);
    
    // タイトルに戻る
    MenuItem *endItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_1(SetSprite::ConfigEnd, this));
    endItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/3 - WINSIZE.height/4));
    
    Menu *menu5 = Menu::create(endItem, NULL);
    menu5->setPosition(Vec2::ZERO);
    this->addChild(menu5, Z_Button);
    
    Label *startLabel = Label::createWithSystemFont("タイトルに戻る", "ArialRoundedMTBold", 25);
    startLabel->setPosition(endItem->getPosition());
    startLabel->setScale(1.2);
    this->addChild(startLabel, Z_Label);
    
    // スコアリセット
    MenuItem *resetItem = MenuItemImage::create("startbtn_result.png", "startbtn_push.png", CC_CALLBACK_0(SetSprite::resetScore, this));
    resetItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/3, WINSIZE.height/3));
    
    Menu *menu6 = Menu::create(resetItem, NULL);
    menu6->setPosition(Vec2::ZERO);
    this->addChild(menu6, Z_Button);
    
    Label *resetLabel = Label::createWithSystemFont("スコアリセット", "ArialRoundedMTBold", 25);
    resetLabel->setPosition(resetItem->getPosition());
    resetLabel->setScale(1.2);
    this->addChild(resetLabel, Z_Label);
}

// ボタンを押すことでゲーム内の画像を変更する
void SetSprite::setNegi()
{
    removeChildByTag(T_Label);
    currentSprite = "ネギ";
    setSpriteLabel();
}

void SetSprite::setBook()
{
    removeChildByTag(T_Label);
    currentSprite = "本";
    setSpriteLabel();
}

void SetSprite::setKabu()
{
    removeChildByTag(T_Label);
    currentSprite = "かぶ";
    setSpriteLabel();
}

void SetSprite::setNinjin()
{
    removeChildByTag(T_Label);
    currentSprite = "にんじん";
    setSpriteLabel();
}

// ラベルの表示
void SetSprite::setSpriteLabel()
{
    Label *viewAngle = Label::createWithSystemFont("", "Arial", 50);
    viewAngle->setPosition(getChildByTag(T_Frame1)->getPosition());
    this->addChild(viewAngle, Z_Label, T_Label);
    
    viewAngle->setString(StringUtils::format("現在の画像:%s", currentSprite.c_str()));
    
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setStringForKey("SpriteName", currentSprite);
    userDef->flush();
    log("画像名表示");
}

// スコアラベルの表示
void SetSprite::setScoreLabel()
{
    UserDefault *userDef = UserDefault::getInstance();
    
    Label *scoreRank1 = Label::createWithSystemFont("", "Arial", 40, Size(getChildByTag(T_Frame2)->getContentSize().width/2,
                                                                          getChildByTag(T_Frame2)->getContentSize().height/4), TextHAlignment::LEFT);
    scoreRank1->setPosition(getChildByTag(T_Frame2)->getPosition().x, getChildByTag(T_Frame2)->getPosition().y + 40);
    this->addChild(scoreRank1, Z_Label, T_Rank1);
    
    scoreRank1->setString(StringUtils::format("RANK1:%d点",userDef->getIntegerForKey("Score1")));
    
    Label *scoreRank2 = Label::createWithSystemFont("", "Arial", 40, Size(getChildByTag(T_Frame2)->getContentSize().width/2,
                                                                          getChildByTag(T_Frame2)->getContentSize().height/4), TextHAlignment::LEFT);
    scoreRank2->setPosition(getChildByTag(T_Frame2)->getPosition());
    this->addChild(scoreRank2, Z_Label, T_Rank2);
    
    scoreRank2->setString(StringUtils::format("RANK2:%d点",userDef->getIntegerForKey("Score2")));
    
    Label *scoreRank3 = Label::createWithSystemFont("", "Arial", 40, Size(getChildByTag(T_Frame2)->getContentSize().width/2,
                                                                          getChildByTag(T_Frame2)->getContentSize().height/4), TextHAlignment::LEFT);
    scoreRank3->setPosition(getChildByTag(T_Frame2)->getPosition().x, getChildByTag(T_Frame2)->getPosition().y - 40);
    this->addChild(scoreRank3, Z_Label, T_Rank3);
    
    scoreRank3->setString(StringUtils::format("RANK3:%d点",userDef->getIntegerForKey("Score3")));
    log("スコアラベル配置");
}


// スコアランキング
void SetSprite::displayScore()
{
    log("スコア判定");
    UserDefault *userDef = UserDefault::getInstance();
    int score = userDef->getIntegerForKey("Score");
    int rank1 = userDef->getIntegerForKey("Score1");
    int rank2 = userDef->getIntegerForKey("Score2");
    int rank3 = userDef->getIntegerForKey("Score3");
    
    log("score:%d",score);
    log("rank1:%d",rank1);
    log("rank2:%d",rank2);
    log("rank3:%d",rank3);
    
    if (rank1 < score)
    {
        userDef->setIntegerForKey("Score1", score);
        userDef->setIntegerForKey("Score2", rank1);
        userDef->setIntegerForKey("Score3", rank2);
        log("ランク1変更");
    }
    else if (rank2 < score)
    {
        userDef->setIntegerForKey("Score2", score);
        userDef->setIntegerForKey("Score3", rank2);
        log("ランク2変更");
    }
    else if (rank3 < score)
    {
        userDef->setIntegerForKey("Score3", score);
        log("ランク3変更");
    }
    else
    {
        log("変更無し");
    }
}

void SetSprite::resetScore()
{
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setIntegerForKey("Score1", 0);
    userDef->setIntegerForKey("Score2", 0);
    userDef->setIntegerForKey("Score3", 0);
    log("スコア初期化");
}

// タイトル画面に戻る
void SetSprite::ConfigEnd(Ref *pSender)
{
    Scene *scene = Title::createScene();
    TransitionScene *effect = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(effect);
    log("遷移:Title");
}
