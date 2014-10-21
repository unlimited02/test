#include "GameScene.h"
#include "ResultText.h"
#include "math.h"
#include "Blade.h"
#include "Kabu.h"
#include "Ninjin.h"
#include "Negi.h"
#include "Book.h"

#include <random>

// 刃の移動量（y方向）
#define DROP_Y 360

// ベーススコア設定
#define BASESCORE_1 20000
#define BASESCORE_2 15000
#define BASESCORE_3 5000
#define BASESCORE_4 2000
#define BASESCORE_5 0

// ベーススコア選択用の境界値
#define DISTANCEBORDER_1 0.5
#define DISTANCEBORDER_2 2
#define DISTANCEBORDER_3 6
#define DISTANCEBORDER_4 10
#define DISTANCEBORDER_5 20

#define WINSIZE     Director::getInstance()->getWinSize()
#define RADIAN      angle * 3.14159265 / 180

#define GETANGLE   getChildByTag(T_Blade)->getRotation() - 90
#define ANGLE       radian * 180 / 3.14159165

Game::Game()
{
}

Game::~Game()
{
    this->removeAllChildren();
    log("解放:Game");
}

// シーン作成
Scene *Game::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = Game::create();

    scene->addChild(layer);
    
    return scene;
}

bool Game::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 背景画像の配置
    setBackGround();

    // 画像の配置
    setSprite();
    
    // ボタンの配置
    setButton();
    
    // 基準位置の配置
    setBorder();
    
    // タッチイベント
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 画像の配置
void Game::setSprite()
{
    UserDefault *userDef = UserDefault::getInstance();
    std::string spriteName = userDef->getStringForKey("SpriteName");

    std::string defaultName1 = "本";
    std::string defaultName2 = "ネギ";
    std::string defaultName3 = "かぶ";
    std::string defaultName4 = "にんじん";
    
    if (strcmp(spriteName.c_str(), defaultName1.c_str()) == 0)
    {
        // 本画像の配置
        this->addChild(BookSprite::create(), Z_Sprite, T_Book);
        root = 1;
    }
    else if (strcmp(spriteName.c_str(), defaultName2.c_str()) == 0)
    {
        // ネギ画像の配置
        this->addChild(NegiSprite::create(), Z_Sprite, T_Negi);
        root = 2;
    }
    else if (strcmp(spriteName.c_str(), defaultName3.c_str()) == 0)
    {
        // かぶ画像の配置
        this->addChild(KabuSprite::create(), Z_Sprite, T_Kabu);
        root = 3;
    }
    else if (strcmp(spriteName.c_str(), defaultName4.c_str()) == 0)
    {
        // にんじん画像の配置
        this->addChild(NinjinSprite::create(), Z_Sprite, T_Ninjin);
        root = 4;
    }
    else
    {
    }
    //　刃物画像の配置
    this->addChild(BladeSprite::create(), Z_Blade, T_Blade);
    log("画像配置");
}

// 背景画像の配置
void Game::setBackGround()
{
    Sprite *bg = Sprite::create("background.png");
    bg->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
    this->addChild(bg, Z_Bg);
    log("背景設定");
}

// ボタンの配置
void Game::setButton()
{
    // リスタートボタン
    MenuItem *reStartImage = MenuItemImage::create("reStartbtn_result.png","reStartbtn._push.png",CC_CALLBACK_0(Game::reStart, this));
    
    reStartImage->setPosition(Vec2(WINSIZE.width/1.3,WINSIZE.height/9));
    
    Menu *menu1 = Menu::create(reStartImage,NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, Z_Button);
    
    Point restartPos = reStartImage->getPosition();
    Label *reStartLabel = Label::createWithSystemFont("やり直し", "ArialRoundedMTBold", 30);
    reStartLabel->setPosition(restartPos.x, restartPos.y);
    this->addChild(reStartLabel, Z_Button);
    log("ボタン配置");
}

// 目印の配置
void Game::setBorder()
{
    UserDefault *userDef = UserDefault::getInstance();
    float setLine = userDef->getFloatForKey("SetLine", 0);

    Point position = getChildByTag(root)->getPosition();
    Size size = getChildByTag(root)->getContentSize();
    float border = position.x - (size.width / setLine);
    
    DrawNode *draw = DrawNode::create();
    draw->drawSegment(Vec2(border, position.y + size.height/2), Vec2(border, position.y - size.height/2), 2.0f, Color4F(.5f, 1.0f, .01f, 10.0f));
    
    this->addChild(draw, Z_Label);

    Label *lineLabel1 = Label::createWithSystemFont("ここで止めろ!", "ArialRoundedMTBold", 30);
    Label *lineLabel2 = Label::createWithSystemFont("↓", "ArialRoundedMTBold", 50);
    
    lineLabel1->setPosition(border, WINSIZE.height/1.05);
    lineLabel2->setPosition(border, WINSIZE.height/1.15);
    
    this->addChild(lineLabel1, Z_Label);
    this->addChild(lineLabel2, Z_Label);
    
    lineLabel1->runAction(action4(border));
    lineLabel2->runAction(action5(border));
    log("目印配置");
}

// 左右動作
FiniteTimeAction *Game::action1(float time)
{
    ActionInterval *move1 = MoveTo::create(time, Vec2(400, 500));
    ActionInterval *ease1 = EaseInOut::create(move1, 3);
    ActionInterval *move2 = MoveTo::create(time, Vec2(550, 500));
    ActionInterval *ease2 = EaseInOut::create(move2, 3);
    ActionInterval *seq = Sequence::create(ease1, ease2, NULL);
    ActionInterval *repeat = RepeatForever::create(seq);
    
    return RepeatForever::create(repeat);
}

// 回転動作
FiniteTimeAction *Game::action2(float time)
{
    ActionInterval *rotate1 = RotateTo::create(time, 110);
    ActionInterval *ease1 = EaseInOut::create(rotate1, 3);
    ActionInterval *rotate2 = RotateTo::create(time, 70);
    ActionInterval *ease2 = EaseInOut::create(rotate2, 3);
    ActionInterval *sequence = Sequence::create(ease1, ease2, NULL);
    ActionInterval *repeat = RepeatForever::create(sequence);

    return RepeatForever::create(repeat);
}

// 下降動作
FiniteTimeAction *Game::action3(float endPoint)
{
    ActionInterval *move = MoveTo::create(0.2, Vec2(endPoint, 100));
    
    return move;
}

// ラベル動作
FiniteTimeAction *Game::action4(float setBorder)
{
    ActionInterval *move1 = MoveTo::create(0.5, Vec2(setBorder, WINSIZE.height/1.03));
    ActionInterval *ease1 = EaseInOut::create(move1, 3);
    ActionInterval *move2 = MoveTo::create(0.5, Vec2(setBorder, WINSIZE.height/1.05));
    ActionInterval *ease2 = EaseInOut::create(move2, 3);
    ActionInterval *sequence = Sequence::create(ease1, ease2, NULL);
    ActionInterval *repeat = RepeatForever::create(sequence);
    
    return RepeatForever::create(repeat);
}

// ラベル動作
FiniteTimeAction *Game::action5(float setBorder)
{
    ActionInterval *move1 = MoveTo::create(0.5, Vec2(setBorder, WINSIZE.height/1.13));
    ActionInterval *ease1 = EaseInOut::create(move1, 3);
    ActionInterval *move2 = MoveTo::create(0.5, Vec2(setBorder, WINSIZE.height/1.15));
    ActionInterval *ease2 = EaseInOut::create(move2, 3);
    ActionInterval *sequence = Sequence::create(ease1, ease2, NULL);
    ActionInterval *repeat = RepeatForever::create(sequence);
    
    return RepeatForever::create(repeat);
}

// タッチ時動作
bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("タッチ");
    tapCount++;

    getChildByTag(T_Blade)->stopAllActions();
    float pointX;

    switch (tapCount)
    {
        case 1: getChildByTag(T_Blade)->runAction(Game::action1(randomTime())); break;
        case 2: getChildByTag(T_Blade)->runAction(Game::action2(randomTime())); break;
        case 3:
            pointX = radianCalculation();
            getChildByTag(T_Blade)->runAction(Game::action3(pointX));
            scoreCalculate(); break;
        case 4:
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeEventListenersForTarget(this);
            endScene(); break;
    }
        return true;
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("タッチ終了");
}

// 刃の移動先座標を算出する
float Game::radianCalculation()
{
    Point pBlade = getChildByTag(T_Blade)->getPosition();
    Point pSprite = getChildByTag(root)->getPosition();
    
    UserDefault *userDef = UserDefault::getInstance();
    float setLine = userDef->getFloatForKey("SetLine", 0);
    
    float angle = GETANGLE;
    float base = DROP_Y * tan(RADIAN);                          // 底辺算出
    float endPoint = pBlade.x - base;                           // 移動先X座標
    
    float height = pBlade.y - pSprite.y;                        // 刃と画像の間隔
    base = height * tan(RADIAN);                                // 画像の中央(Y)上での底辺
    float bladePass = pBlade.x - base;                          // 通過点
    
    Size size = getChildByTag(root)->getContentSize();
    float pointX2 = pSprite.x - (size.width / setLine);         // 判定用の基準点
    distance = pointX2 - bladePass;                             // 基準点と通過点の間隔
    
    float spriteEdge = pSprite.x - (size.width / 2.0);          // 画像の端のX座標
    
    if (bladePass > spriteEdge)
    {
        log("範囲内");
    } else {
        distance = 3776;
        log("範囲外");
    }
    
    if ( distance < 0)                                          // 負の値なら正の値に変換
    {
        distance = distance * (-1);
    }
    
    // スコアデータの保存
    userDef = UserDefault::getInstance();
    userDef->setFloatForKey("scoreDistance", distance);
    userDef->setFloatForKey("scoreBlade", bladePass);
    userDef->setFloatForKey("scoreAngle", angle);
    userDef->flush();

    return endPoint;
}

// スコア計算
void Game::scoreCalculate()
{
    int baseScore;
    
    if (distance <= DISTANCEBORDER_1)
    {
        baseScore = BASESCORE_1 * BASESCORE_1;
    }
    else if (distance <= DISTANCEBORDER_2)
    {
        baseScore = BASESCORE_1;
    }
    else if (distance <= DISTANCEBORDER_3)
    {
        baseScore = BASESCORE_2;
    }
    else if (distance <= DISTANCEBORDER_4)
    {
        baseScore = BASESCORE_3;
    }
    else if (distance <= DISTANCEBORDER_5)
    {
        baseScore = BASESCORE_4;
    }
    else
    {
        baseScore = BASESCORE_5;
    }
    
    int sAngle = GETANGLE;
    
    if ( sAngle < 0 )
    {
        sAngle = sAngle * (-1);
    }

    int sTraction1 = distance * distance;
    int sTraction2 = sAngle * 500;
    int score = baseScore - sTraction1 - sTraction2;
    
    log("ベース:%d",baseScore);
    log("減点1:%d",sTraction1);
    log("減点2:%d",sTraction2);
    log("スコア:%d",score);

    // スコアデータの保存
    UserDefault *userDef = UserDefault::getInstance();
    userDef->setIntegerForKey("Score", score);
    userDef->flush();
}

// アクション動作の速度
float Game::randomTime()
{
    int rootTime = 6;
    float time;
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    int random = std::uniform_int_distribution<int>(0,rootTime)(rand);
    
    switch (random)
    {
        case 0: time = 2.0; break;
        case 1: time = 1.5; break;
        case 2: time = 1.0; break;
        case 3: time = 0.95; break;
        case 4: time = 0.9; break;
        case 5: time = 0.8; break;
        default: time = 0.3; break;
    }
    return time;
}

// ゲームのリスタート
void Game::reStart()
{
    Scene *scene = Game::createScene();
    TransitionScene *effect = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(effect);
    log("リスタート");
}

// リザルト画面への画面遷移
void Game::endScene()
{
    Scene *scene = resultText::createScene();
    TransitionScene *effect = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->pushScene(effect);
    log("画面遷移:resultText");
}
