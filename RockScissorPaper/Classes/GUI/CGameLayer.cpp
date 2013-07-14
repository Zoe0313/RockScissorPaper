//
//  CGameLayer.cpp
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-6-27.
//
//
#include "SimpleAudioEngine.h"
#include "CGameLayer.h"
#include "CUtility.h"
#include "CMenuLayer.h"
#include "CUserData.h"

const char* cstGameBg = "game_bg0.png";
const char* cstReturnNormalBtn = "game_back.png";
const char* cstReturnPressedBtn = "game_back1.png";

const char* cstScoreList[cstScoreLblCnt] =
{
    "胜: ",
    "负: ",
    "平: "
};
const char* cstUpHandBtnList[cstHandBtnCnt] =
{
    "game_robot_bu.png",
    "game_robot_shitou.png",
    "game_robot_jiandao.png"
};
const char* cstDownHandBtnList[cstHandBtnCnt] =
{
    "game_player_jiandao.png",
    "game_player_shitou.png",
    "game_player_bu.png"
};

const char* cstWinEffect = "victory.caf";
const char* cstFailEffect = "defeat.aif";
const char* cstDeuceEffect = "draw.aif";
extern const char* cstButtonEffect;

// opponent's rock scissor paper index 
#define UpPaperHand 0
#define UpRockHand 1
#define UpScissorHand 2

// my rock scissor paper index 
#define DownScissorHand 0
#define DownRockHand 1
#define DownPaperHand 2

// score index
#define WIN 0
#define FAIL 1
#define DEUCE 2

using namespace cocos2d;

CGameLayer* CGameLayer::create()
{
    CGameLayer* pLayer = new CGameLayer();
    pLayer->autorelease();
    pLayer->init();
    return pLayer;
}

CCScene* CGameLayer::scene()
{
    CCScene *scene = CCScene::create();
    CGameLayer *pLayer = CGameLayer::create();
    scene->addChild(pLayer);
    
    return scene;
}

bool CGameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // get score info
    ScoreInfo_t scoreInfo;
    if(CUserData::sharedSettingData()->getNewScoreData(scoreInfo))
    {
        m_iScore[WIN] = scoreInfo.iWin;
        m_iScore[FAIL] = scoreInfo.iFail;
        m_iScore[DEUCE] = scoreInfo.iDeuce;
    }
    else
    {
        m_iScore[WIN] = 0;
        m_iScore[FAIL] = 0;
        m_iScore[DEUCE] = 0;
    }
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 2);
    
    // return menu button 
    m_pReturnItem = CCMenuItemImage::create(cstReturnNormalBtn,cstReturnPressedBtn,this,menu_selector(CGameLayer::OnReturnMenu) );
    float fReturnWidth = m_pReturnItem->getContentSize().width;
    float fReturnHeight = m_pReturnItem->getContentSize().height;
    float fReturnPosY = CUtility::GetWindowSizeHeight() - fReturnHeight;
    m_pReturnItem->setPosition( ccp(fReturnWidth, fReturnPosY) );
    m_pReturnItem->setEnabled(true);
    pMenu->addChild(m_pReturnItem, 2);
    
    // score label
    char textBuf[32] = {0};
    float fScorePosX = fReturnWidth*3;
    for (int i = 0; i < cstScoreLblCnt; i++)
    {
        CCLabelTTF* pScoreLabel = CCLabelTTF::create(cstScoreList[i], "Thonburi", 36);
        pScoreLabel->setPosition( ccp(fScorePosX, fReturnPosY) );
        pScoreLabel->setColor(ccBLACK);
        this->addChild(pScoreLabel, 2);
  
        sprintf(textBuf, "%d", m_iScore[i]);
        m_pNumberLabel[i] = CCLabelTTF::create(textBuf, "Thonburi", 36);
        m_pNumberLabel[i]->setPosition( ccp(fScorePosX+60, fReturnPosY) );
        m_pNumberLabel[i]->setColor(ccRED);
        this->addChild(m_pNumberLabel[i], 2);
        
        fScorePosX += fReturnWidth*1.5;
    }
    
    // opponent's rock scissor paper button
    for(int i = 0; i < cstHandBtnCnt; i++)
    {
        CCMenuItemImage* pHandItem = CCMenuItemImage::create(cstUpHandBtnList[i], cstUpHandBtnList[i], this, NULL);
        m_fUpHandPos[i].x = CUtility::GetWindowCenterPoint().x + pHandItem->getContentSize().width*(i-1);
        m_fUpHandPos[i].y = CUtility::GetWindowCenterPoint().y + pHandItem->getContentSize().height/2 + 60;
        pHandItem->setPosition(ccp(m_fUpHandPos[i].x, m_fUpHandPos[i].y));
        this->addChild(pHandItem, 2);
        
        m_UpSprite[i] = CCSprite::create(cstUpHandBtnList[i]);
        m_UpSprite[i]->setPosition(m_fUpHandPos[i]);
        m_UpSprite[i]->setVisible(false);
        this->addChild(m_UpSprite[i], 3);
    }
    
    // my rock scissor paper button
    for(int i = 0; i < cstHandBtnCnt; i++)
    {
        m_pHandItem[i] = CCMenuItemImage::create(cstDownHandBtnList[i], cstDownHandBtnList[i], this, menu_selector(CGameLayer::OnClickButton));
        m_fDownHandPos[i].x = CUtility::GetWindowCenterPoint().x + m_pHandItem[i]->getContentSize().width*(i-1);
        m_fDownHandPos[i].y = CUtility::GetWindowCenterPoint().y - m_pHandItem[i]->getContentSize().height*1.5;
        m_pHandItem[i]->setPosition(ccp(m_fDownHandPos[i].x, m_fDownHandPos[i].y));
        m_pHandItem[i]->setEnabled(true);
        m_pHandItem[i]->setTag(i);
        pMenu->addChild(m_pHandItem[i]);
        
        m_DownSprite[i] = CCSprite::create(cstDownHandBtnList[i]);
        m_DownSprite[i]->setPosition(m_fDownHandPos[i]);
        m_DownSprite[i]->setVisible(false);
        this->addChild(m_DownSprite[i],3);
    }
    
    // create game background
    CCSprite* pSprite = CCSprite::create(cstGameBg);
    pSprite->setPosition(CUtility::GetWindowCenterPoint());
    this->addChild(pSprite, 0);
    
    return true;
}


void CGameLayer::OnReturnMenu(CCObject* pSender)
{
    // set score info
    ScoreInfo_t scoreInfo;
    scoreInfo.strDate = CUserData::sharedSettingData()->getCurrentDate();
    scoreInfo.iWin = m_iScore[WIN];
    scoreInfo.iFail = m_iScore[FAIL];
    scoreInfo.iDeuce = m_iScore[DEUCE];
    
    CUserData::sharedSettingData()->setScoreData(scoreInfo);
    
    // transition scene
    CCScene *pScene = CMenuLayer::scene();
    CCScene *transitionScene = CCTransitionMoveInL::create(0.5f, pScene);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
    // return button effect
    if(CUserData::sharedSettingData()->getEffectMusicStatus())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstButtonEffect, false);
    }
}


void CGameLayer::OnClickButton(CCObject* pSender)
{
    if(!m_pReturnItem->isEnabled())
    {
        return;
    }
    
    m_pReturnItem->setEnabled(false);// return menu button can't pressed
    for(int i = 0; i < cstHandBtnCnt; i++)
    {
        m_pHandItem[i]->setEnabled(false);// hand button can't pressed
    }
    
    // my hand index
    CCNode *node = (CCNode *)pSender;
    int iDownIndex = node->getTag();
    if(iDownIndex < 0 || iDownIndex > 2)
    {
        return;
    }
    
    // opponent's hand index
    int iUpIndex = rand()%3;
    
    m_UpSprite[iUpIndex]->setPosition(m_fUpHandPos[iUpIndex]);
    m_DownSprite[iDownIndex]->setPosition(m_fDownHandPos[iDownIndex]);
    for(int i = 0; i < cstHandBtnCnt; i++)
    {
        // my hand visible
        if(iDownIndex == i)
        {
            m_DownSprite[i]->setVisible(true);
        }
        else
        {
            m_DownSprite[i]->setVisible(false);
        }
        
        // opponent's hand visible
        if(iUpIndex == i)
        {
            m_UpSprite[i]->setVisible(true);
        }
        else
        {
            m_UpSprite[i]->setVisible(false);
        }
    }

    // my hand move to
    CCMoveTo* moveUp = CCMoveTo::create(0.3, ccp(CUtility::GetWindowCenterPoint().x + 70, CUtility::GetWindowCenterPoint().y - 115));
    CCSequence* moveUpSequence = CCSequence::create(moveUp,NULL);
    CCRepeat* repeatUp = CCRepeat::create(moveUpSequence, 1);
    m_DownSprite[iDownIndex]->runAction(repeatUp);
    m_DownSprite[iDownIndex]->isRunning();
    
    // opponent's hand visible
    CCMoveTo* moveDown = CCMoveTo::create(0.3, ccp(CUtility::GetWindowCenterPoint().x - 60, CUtility::GetWindowCenterPoint().y - 20));
    CCCallFunc* callBack = CCCallFunc::create(this, callfunc_selector(CGameLayer::OnEnableAllButton));
    CCSequence* moveDownSequence = CCSequence::create(moveDown,callBack,NULL);
    CCRepeat* repeatDown = CCRepeat::create(moveDownSequence, 1);
    m_UpSprite[iUpIndex]->runAction(repeatDown);
    
    // update score
    updateScore(iUpIndex, iDownIndex);
}


void CGameLayer::OnEnableAllButton()
{
    for(int i = 0; i < cstHandBtnCnt; i++)
    {
        m_pHandItem[i]->setEnabled(true);// hand button can pressed
    }
    m_pReturnItem->setEnabled(true);// return menu button can pressed
}

void CGameLayer::updateScore(int iUpIndex, int iDownIndex)
{
    bool bWin = false;
    bool bFail = false;
    bool bDeuce = false;
    
    // update score 
    if(iUpIndex == UpPaperHand)
    {
        if(iDownIndex == DownScissorHand)
        {
            m_iScore[WIN]++;
            bWin = true;
        }
        else if (iDownIndex == DownRockHand)
        {
            m_iScore[FAIL]++;
            bFail = true;
        }
        else if(iDownIndex == DownPaperHand)
        {
            m_iScore[DEUCE]++;
            bDeuce = true;
        }
    }
    else if(iUpIndex == UpRockHand)
    {
        if(iDownIndex == DownScissorHand)
        {
            m_iScore[FAIL]++;
            bFail = true;
        }
        else if (iDownIndex == DownRockHand)
        {
            m_iScore[DEUCE]++;
            bDeuce = true;
        }
        else if(iDownIndex == DownPaperHand)
        {
            m_iScore[WIN]++;
            bWin = true;
        }
    }
    else if(iUpIndex == UpScissorHand)
    {
        if(iDownIndex == DownScissorHand)
        {
            m_iScore[DEUCE]++;
            bDeuce = true;
        }
        else if (iDownIndex == DownRockHand)
        {
            m_iScore[WIN]++;
            bWin = true;
        }
        else if(iDownIndex == DownPaperHand)
        {
            m_iScore[FAIL]++;
            bFail = true;
        }
    }
    
    // update score label 
    char textBuf[20] = {0};
    for (int i = 0; i < cstScoreLblCnt; i++)
    {
        sprintf(textBuf, "%d", m_iScore[i]);
        m_pNumberLabel[i]->setString(textBuf);
    }
    
    // play effect
    if(CUserData::sharedSettingData()->getEffectMusicStatus())
    {
        if(bWin)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstWinEffect, false);
        }
        else if(bFail)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstFailEffect, false);
        }
        else if(bDeuce)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstDeuceEffect, false);
        }
    }
}


