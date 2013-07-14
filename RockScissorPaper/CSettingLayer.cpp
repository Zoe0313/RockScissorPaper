//
//  CSettingLayer.cpp
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-2.
//
//

#include "CSettingLayer.h"
#include "SimpleAudioEngine.h"
#include "CUtility.h"
#include "CMenuLayer.h"
#include "CUserData.h"

const char* cstSettingBg = "game_bg2.png";
const char* cstSettingBtn = "setting_button.png";
extern const char* cstReturnNormalBtn;
extern const char* cstReturnPressedBtn;

extern const char* cstButtonEffect;
extern const char* cstBgMusic;

const char* cstCloseBtnList[cstSettingBtnCnt] =
{
    "关闭音乐",
    "关闭音效"
};

const char* cstOpenBtnList[cstSettingBtnCnt] =
{
    "打开音乐",
    "打开音效"
};

using namespace cocos2d;

static bool g_bPauseBgMusic = false;

CSettingLayer::CSettingLayer()
:m_bOpenBgMusic(false),
m_bOpenEffectMusic(false)
{
}

CSettingLayer* CSettingLayer::create()
{
    CSettingLayer* pLayer = new CSettingLayer();
    pLayer->autorelease();
    pLayer->init();
    
    return pLayer;
}

CCScene* CSettingLayer::scene()
{
    CCScene *scene = CCScene::create();
    CSettingLayer *pLayer = CSettingLayer::create();
    scene->addChild(pLayer);
    
    return scene;
}

bool CSettingLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }

    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    // return menu button
    CCMenuItemImage *pReturnItem = CCMenuItemImage::create(cstReturnNormalBtn,cstReturnPressedBtn,this,menu_selector(CSettingLayer::OnReturnMenu) );
    float fReturnWidth = pReturnItem->getContentSize().width;
    float fReturnHeight = pReturnItem->getContentSize().height;
    float fReturnPosY = CUtility::GetWindowSizeHeight() - fReturnHeight;
    pReturnItem->setPosition( ccp(fReturnWidth, fReturnPosY) );
    pReturnItem->setEnabled(true);
    pMenu->addChild(pReturnItem, 2);
    
    // setting button 
    float fBtnPosX = CUtility::GetWindowCenterPoint().x;
    float fBtnPosY = CUtility::GetWindowCenterPoint().y + 200.f;
    float fBtnHeight = 80.f;
    
    for (int i = 0; i < cstSettingBtnCnt; i++)
    {
        CCMenuItemImage *pMusicControlItem = CCMenuItemImage::create(cstSettingBtn,cstSettingBtn,this,menu_selector(CSettingLayer::OnClickButton) );
        pMusicControlItem->setPosition( ccp(fBtnPosX, fBtnPosY) );
        pMusicControlItem->setScaleX(3.2f);
        pMusicControlItem->setScaleY(1.3f);
        pMusicControlItem->setTag(i);
        pMenu->addChild(pMusicControlItem);
        
        m_pControlLabel[i] = CCLabelTTF::create("", "Thonburi", 34);
        m_pControlLabel[i]->setPosition( ccp(fBtnPosX, fBtnPosY) );
        m_pControlLabel[i]->setColor(ccBLACK);
        this->addChild(m_pControlLabel[i], 2);
        
        fBtnPosY -= fBtnHeight + 20.f;
    }
    
    m_bOpenBgMusic = CUserData::sharedSettingData()->getBgMusicStatus();
    if(m_bOpenBgMusic)
    {
        m_pControlLabel[0]->setString(cstCloseBtnList[0]);
    }
    else
    {
         m_pControlLabel[0]->setString(cstOpenBtnList[0]);
    }

    m_bOpenEffectMusic = CUserData::sharedSettingData()->getEffectMusicStatus();
    if(m_bOpenEffectMusic)
    {
        m_pControlLabel[1]->setString(cstCloseBtnList[1]);
    }
    else
    {
        m_pControlLabel[1]->setString(cstOpenBtnList[1]);
    }
    
    // create setting background
    CCSprite* pSprite = CCSprite::create(cstSettingBg);
    pSprite->setPosition(CUtility::GetWindowCenterPoint());
    this->addChild(pSprite, 0);
    
    return true;
}

void CSettingLayer::OnReturnMenu(CCObject* menuItem)
{
    CCScene *pScene = CMenuLayer::scene();
    CCScene *transitionScene = CCTransitionMoveInL::create(0.5f, pScene);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
    if(m_bOpenEffectMusic)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstButtonEffect, false);
    }
}

void CSettingLayer::OnClickButton(CCObject* menuItem)
{
    CCNode *node = (CCNode *)menuItem;
    int iIndex = node->getTag();
    
    if(0 == iIndex)
    {
        m_bOpenBgMusic = !m_bOpenBgMusic;
        
        if(m_bOpenBgMusic)
        {
            m_pControlLabel[0]->setString(cstCloseBtnList[0]);
            
            if(g_bPauseBgMusic)
            {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
            }
            else
            {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(cstBgMusic, true);
            }
        }
        else
        {
            m_pControlLabel[0]->setString(cstOpenBtnList[0]);
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
            g_bPauseBgMusic = true;
        }
        CUserData::sharedSettingData()->setBgMusicStatus(m_bOpenBgMusic);
    }
    else if (1 == iIndex)
    {
        m_bOpenEffectMusic = !m_bOpenEffectMusic;
        
        if(m_bOpenEffectMusic)
        {
            m_pControlLabel[1]->setString(cstCloseBtnList[1]);
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstButtonEffect, false);
        }
        else
        {
            m_pControlLabel[1]->setString(cstOpenBtnList[1]);
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        }
        CUserData::sharedSettingData()->setEffectMusicStatus(m_bOpenEffectMusic);
    }
}