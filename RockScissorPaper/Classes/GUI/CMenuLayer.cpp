#include "CMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "CUtility.h"
#include "CGameLayer.h"
#include "CResultLayer.h"
#include "CSettingLayer.h"
#include "CUserData.h"

const char* cstMenuBtn = "main_btnnormal.png";
const char* cstMenuBg = "main_bg.png";

const int cstMenuBtnCnt = 4;
const char* cstMenuBtnList[cstMenuBtnCnt] =
{
    "开始游戏",
    "得分记录",
    "音乐设置",
    "退出游戏"
};

const char* cstButtonEffect = "button.wav";
const char* cstBgMusic = "background.mp3";

using namespace cocos2d;

CMenuLayer* CMenuLayer::create()
{
    CMenuLayer* pLayer = new CMenuLayer();
    pLayer->autorelease();
    pLayer->init();
    return pLayer;
}

CCScene* CMenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    CMenuLayer *pLayer = CMenuLayer::create();
    scene->addChild(pLayer);

    return scene;
}

bool CMenuLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    // create menu button
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    float fBtnPosX = CUtility::GetWindowCenterPoint().x;
    float fBtnPosY = CUtility::GetWindowCenterPoint().y + 90.f;
    float fBtnHeight = CCSprite::create(cstMenuBtn)->getTextureRect().size.height;
    for(int i = 0; i < cstMenuBtnCnt; i++)
    {
        CCMenuItemImage *pMenuItem = CCMenuItemImage::create(cstMenuBtn,cstMenuBtn,this,menu_selector(CMenuLayer::menuCallback) );
        pMenuItem->setPosition( ccp(fBtnPosX, fBtnPosY) );
        pMenuItem->setTag(i);
        pMenu->addChild(pMenuItem);
        
        CCLabelTTF* pMenuLabel = CCLabelTTF::create(cstMenuBtnList[i], "Thonburi", 34);
        pMenuLabel->setPosition( ccp(fBtnPosX, fBtnPosY) );
        pMenuLabel->setColor(ccBLACK);
        this->addChild(pMenuLabel, 2);
        
        fBtnPosY -= fBtnHeight + 10.f;
    }

    // create game title label 
    CCLabelTTF* pLabel = CCLabelTTF::create("石头剪刀布", "Thonburi", 48);
    pLabel->setPosition( ccp(CUtility::GetWindowCenterPoint().x, CUtility::GetWindowCenterPoint().y + 250.f) );
    pLabel->setColor(ccBLACK);
    this->addChild(pLabel, 1);

    // create menu background
    CCSprite* pSprite = CCSprite::create(cstMenuBg);
    pSprite->setPosition(CUtility::GetWindowCenterPoint());
    this->addChild(pSprite, 0);
    
    // play background music
    if(CUserData::sharedSettingData()->getBgMusicStatus()
    && !CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
    }
    return true;
}

void CMenuLayer::menuCallback(CCObject* pSender)
{
    if(CUserData::sharedSettingData()->getEffectMusicStatus())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstButtonEffect, false);
    }
    
    CCNode *node = (CCNode *)pSender;
    int menuIndex = node->getTag();
    
    CCScene* transitionScene = NULL;
    switch (menuIndex)
    {
        case 0:
            {
                CCScene *pScene = CGameLayer::scene();
                transitionScene = CCTransitionMoveInR::create(0.5f, pScene);
                CCDirector::sharedDirector()->replaceScene(transitionScene);
            }
            break;
        case 1:
            {
                CCScene* pScene = CResultLayer::scene();
                transitionScene = CCTransitionMoveInR::create(0.5f, pScene);
                CCDirector::sharedDirector()->replaceScene(transitionScene);
            }
            break;
        case 2:
            {
                CCScene *pScene = CSettingLayer::scene();
                transitionScene = CCTransitionMoveInR::create(0.5f, pScene);
                CCDirector::sharedDirector()->replaceScene(transitionScene);
            }
            break;
        case 3:
            CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
            break;
        default:
            break;
    }
}
