#include "GameScene.h"
#include "ResultText.h"
#include "SpriteSetScene.h"
#include "SaveSQL.h"

#define WINSIZE Director::getInstance()->getWinSize()

// コメントランク選択用の境界点
#define SCOREBORDER_1 score<3000
#define SCOREBORDER_2 score<6000
#define SCOREBORDER_3 score<14000
#define SCOREBORDER_4 score<19000

resultText::resultText()
{
}

resultText::~resultText()
{
    log("解放:resultText");
    this->removeAllChildren();
}

// シーンの作成
Scene *resultText::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = resultText::create();

    scene->addChild(layer);
    
    return scene;
}

bool resultText::init()
{
    if(!Layer::init())
    {
        return false;
    }

    // スコア更新
    SetSprite::displayScore();
    
    // 背景の配置
    initSetBackGround();
    
    // ボタンの配置
    initSetButton();
    
    // テキストの設定
    textSelect();
    
    // テキストの表示
    displayText();
    
    return true;
}

void resultText::initSetBackGround()
{
    Sprite *Bg = Sprite::create("mokumeBG.png");
    Bg->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/2));
    this->addChild(Bg, Z_Bg);
}

void resultText::initSetButton()
{
    // 画像の変更画面
    MenuItem *configItem = MenuItemImage::create("reStartbtn_result.png",
                                                 "reStartbtn._push.png", CC_CALLBACK_0(resultText::spriteConfig, this));
    configItem->setPosition(Vec2(WINSIZE.width/2 - WINSIZE.width/4,
                                 WINSIZE.height/9));
    
    Menu *menu1 = Menu::create(configItem, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, Z_Button);
    
    Point configPos = configItem->getPosition();
    auto configLabel = Label::createWithSystemFont("画像を変える", "ArialRoundedMTBold", 30);
    configLabel->setPosition(configPos.x, configPos.y);
    addChild(configLabel, Z_Label);
    
    // リスタートボタン
    MenuItem *reStartItem = MenuItemImage::create("reStartbtn_result.png",
                                                  "reStartbtn._push.png", CC_CALLBACK_0(resultText::reStart,  this));
    reStartItem->setPosition(Vec2(WINSIZE.width/2, WINSIZE.height/9));
    
    Menu *menu2 = Menu::create(reStartItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, Z_Button);
    
    Point reStartPos = reStartItem->getPosition();
    auto reStartLabel = Label::createWithSystemFont("もっとやる", "ArialRoundedMTBold", 30);
    reStartLabel->setPosition(reStartPos.x, reStartPos.y);
    addChild(reStartLabel, Z_Label);
    
    // 終了ボタン
    MenuItem *closeItem = MenuItemImage::create("endbtn_result.png",
                                                "endbtn_push.png", CC_CALLBACK_1(resultText::gameEnd, this));
    closeItem->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/4,
                                WINSIZE.height/9));
    
    Menu *menu3 = Menu::create(closeItem, NULL);
    menu3->setPosition(Vec2::ZERO);
    this->addChild(menu3, Z_Button);
    
    Point pClose = closeItem->getPosition();
    Label *closeLabel = Label::createWithSystemFont("やめる", "ArialRoundedMTBold", 30);
    closeLabel->setPosition(pClose.x, pClose.y);
    addChild(closeLabel, Z_Label);
    log("ボタン配置");
}

// テキストの設定
void resultText::textSelect()
{
    // スコアデータの取得
    UserDefault *userDef = UserDefault::getInstance();
    float tempScore = userDef->getIntegerForKey("Score", 0);
    
    int textRoot;
    score = tempScore;
    
    if (SCOREBORDER_1)
    {
        textRoot = 1;
    }
    else if (SCOREBORDER_2)
    {
        textRoot = 2;
    }
    else if (SCOREBORDER_3)
    {
        textRoot = 3;
    }
    else if (SCOREBORDER_4)
    {
        textRoot = 4;
    }
    else
    {
        textRoot = 5;
    }
    
    texts(textRoot);
}

// データベースからコメントを抽出
void resultText::texts(int textRoot)
{
    log("DBアクセス");
    const char *name;
    
    for (int roop = 0 ; roop < 3 ; roop++)
    {
        switch (roop)
        {
            case 0: name = "A"; break;
            case 1: name = "B"; break;
            case 2: name = "C"; break;
        }
        
        // ランダム値の生成
        int commentNumber = 5;
        std::random_device rd;
        std::mt19937 rand = std::mt19937(rd());
        int random = std::uniform_int_distribution<int>(1, commentNumber)(rand);
        
        // データベースにアクセス
        const char *comment = SaveSQL::sqliteGetValueForKey(textRoot, name, random);
        arrayText.push_back(comment);
    }
}

// テキストの表示
void resultText::displayText()
{
    // 保存データの読み込み
    UserDefault *userDef = UserDefault::getInstance();
    
    float angle = userDef->getFloatForKey("scoreAngle", 0);
    float resultAngle = angle;
    
    if ( resultAngle < 0 )
    {
        resultAngle = resultAngle * (-1);
    }
    
    float distance = userDef->getFloatForKey("scoreDistance", 0);
    float resultDistance = distance;
    
    // 角度表示
    Label *viewAngle = Label::createWithSystemFont("a", "Arial", 50);
    viewAngle->setPosition(WINSIZE.width/2, WINSIZE.height/1.2);
    addChild(viewAngle);
    
    viewAngle->setString(StringUtils::format("角度:%0.2f°", resultAngle));
    log("%0.2f°",resultAngle);
    
    // 距離表示
    Label *viewPixel = Label::createWithSystemFont("", "Arial", 50);
    viewPixel->setPosition(WINSIZE.width/2, WINSIZE.height/1.37);
    addChild(viewPixel);
    
    viewPixel->setString(StringUtils::format("背表紙のりまでの間隔:%0.2fピクセル", resultDistance));
    log("%0.2fピクセル", resultDistance);
    
    // 点数表示
    Label *viewScore = Label::createWithSystemFont("", "Arial", 50);
    viewScore->setPosition(WINSIZE.width/2, WINSIZE.height/1.6);
    addChild(viewScore);

    viewScore->setString(StringUtils::format("点数:%d", score));
    
    // 評価文章表示
    Label *viewText1 = Label::createWithSystemFont(arrayText[0], "Arial", 27);
    viewText1->setPosition(WINSIZE.width/2, 300);
    addChild(viewText1);

    Label *viewText2 = Label::createWithSystemFont(arrayText[1], "Arial", 27);
    viewText2->setPosition(WINSIZE.width/2, 250);
    addChild(viewText2);
    
    Label *viewText3 = Label::createWithSystemFont(arrayText[2], "Arial", 27);
    viewText3->setPosition(WINSIZE.width/2, 200);
    addChild(viewText3);
    
    viewText1->setString(StringUtils::format("プロジェクトマネージャー...%s", arrayText[0].c_str()));
    viewText2->setString(StringUtils::format("慇懃無礼な商人...%s", arrayText[1].c_str()));
    viewText3->setString(StringUtils::format("C...%s", arrayText[2].c_str()));
    log("ラベル配置");
}

void resultText::spriteConfig()
{
    Scene *scene = SetSprite::createScene();
    TransitionScene *effect = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(effect);
    log("遷移:SetSprite");
}

// リスタート
void resultText::reStart()
{
    Scene *scene = Game::createScene();
    TransitionScene *effect = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(effect);
    log("リスタート");
}

// アプリ終了イベント
void resultText::gameEnd(Ref *pSender)
{
    Director::getInstance()->end();
    exit(0);
    log("終了");
}
