#include "HelloWorldScene.h"
#include "BeaconBridge.hpp"
#include "GameSettings.hpp"

#define WINSIZE Director::getInstance()->getWinSize()
#define WINCENTER Point(WINSIZE.width*0.5, WINSIZE.height*0.5)

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    this->setup();
    
    return true;
}

void HelloWorld::setup()
{
    // スタートボタン
    Sprite* btnStart_ON = Sprite::create();
    btnStart_ON->setTextureRect(Rect(0, 0, 200, 100));
    btnStart_ON->setColor(Color3B::GRAY);
    
    Sprite* btnStart_OFF = Sprite::create();
    btnStart_OFF->setTextureRect(Rect(0, 0, 200, 100));
    btnStart_OFF->setColor(Color3B(200, 50, 50));
    
    MenuItemSprite* btnStart = MenuItemSprite::create(btnStart_OFF,
                                                         btnStart_ON,
                                                         [this](Ref* sender) {this->startTapped((MenuItemSprite*)sender);});
    Label* lblStart = Label::createWithSystemFont("START", "Arial", 25);
    lblStart->setAlignment(TextHAlignment::CENTER);
    lblStart->setPosition(Vec2(btnStart->getContentSize().width*0.5, btnStart->getContentSize().height*0.5));
    btnStart->addChild(lblStart);
    
    // ストップボタン
    Sprite* btnStop_ON = Sprite::create();
    btnStop_ON->setTextureRect(Rect(0, 0, 200, 100));
    btnStop_ON->setColor(Color3B::GRAY);
    
    Sprite* btnStop_OFF = Sprite::create();
    btnStop_OFF->setTextureRect(Rect(0, 0, 200, 100));
    btnStop_OFF->setColor(Color3B(200, 200, 50));
    
    MenuItemSprite* btnStop = MenuItemSprite::create(btnStop_OFF,
                                                      btnStop_ON,
                                                      [this](Ref* sender) {this->stopTapped((MenuItemSprite*)sender);});
    Label* lblStop = Label::createWithSystemFont("STOP", "Arial", 25);
    lblStop->setAlignment(TextHAlignment::CENTER);
    lblStop->setPosition(Vec2(btnStop->getContentSize().width*0.5, btnStop->getContentSize().height*0.5));
    btnStop->addChild(lblStop);
    
    Menu* menu = Menu::create(btnStart, btnStop, NULL);
    menu->alignItemsVerticallyWithPadding(50);
    menu->setPosition(Vec2(WINCENTER.x, WINCENTER.y));
    this->addChild(menu);
    
    Label* lblUUID = Label::createWithSystemFont("", "Arial", 20);
    lblUUID->setAlignment(TextHAlignment::CENTER);
    lblUUID->setPosition(Vec2(WINCENTER.x, WINSIZE.height-20));
    this->addChild(lblUUID);

    // UUIDチェック
    if (GS->getUUID().length()) {
        lblUUID->setString(GS->getUUID());
        
        // Beacon初期化
        BeaconBridge::initBeacon(GS->getUUID());
        
    } else {
        // UUID取得する
        std::string uuid = BeaconBridge::initBeaconUUID();
        if (uuid.length()) {
            GS->setUUID(uuid);
            lblUUID->setString(GS->getUUID());
            
            // Beacon初期化
            BeaconBridge::initBeacon(GS->getUUID());
            
        }
    }

}

// ビーコン発信
void HelloWorld::startTapped(cocos2d::MenuItemSprite *sender)
{
    BeaconBridge::beaconAction(true, [=](bool flg)
    {
        log("start done!");
        
    });
    
}

// ビーコン停止
void HelloWorld::stopTapped(cocos2d::MenuItemSprite *sender)
{
    BeaconBridge::beaconAction(false, [=](bool flg)
    {
        log("stop done!");
    });
    
}
