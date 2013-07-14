//
//  CResultLayer.cpp
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-2.
//
//

#include "SimpleAudioEngine.h"
#include "CResultLayer.h"
#include "CMenuLayer.h"
#include "CUserData.h"
#include "CUtility.h"
#include "CGameLayer.h"

const char* cstResultBg = "game_bg1.png";
extern const char* cstButtonEffect;
extern const char* cstReturnNormalBtn;
extern const char* cstReturnPressedBtn;
extern const char* cstScoreList[cstScoreLblCnt];
extern const int cstLineMaxCnt;

using namespace cocos2d;
using namespace std;

CCScene* CResultLayer::scene()
{
    CCScene* scene = CCScene::create();
    CResultLayer* layer = CResultLayer::create();
    scene->addChild(layer);
    
    return scene;
}

CResultLayer* CResultLayer::create()
{
    CResultLayer* pLayer = new CResultLayer();
    pLayer->autorelease();
    pLayer->init();
    
    return pLayer;
}

bool CResultLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    setScoreData();
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    // return menu button
    CCMenuItemImage *pReturnItem = CCMenuItemImage::create(cstReturnNormalBtn,cstReturnPressedBtn,this,menu_selector(CResultLayer::OnReturnMenu) );
    float fReturnWidth = pReturnItem->getContentSize().width;
    float fReturnHeight = pReturnItem->getContentSize().height;
    float fReturnPosY = CUtility::GetWindowSizeHeight() - fReturnHeight;
    pReturnItem->setPosition( ccp(fReturnWidth, fReturnPosY) );
    pReturnItem->setEnabled(true);
    pMenu->addChild(pReturnItem, 2);
    
    float fTitlePosX = 390;
    float fTitlePosY = CUtility::GetWindowSizeHeight() - 150;
    for (int i = 0; i < cstScoreLblCnt; i++)
    {
        CCLabelTTF* pTitle = CCLabelTTF::create(cstScoreList[i], "Thonburi", 36);
        pTitle->setPosition( ccp(fTitlePosX, fTitlePosY) );
        pTitle->setColor(ccBLACK);
        this->addChild(pTitle, 2);
        
        fTitlePosX += 100;
    }
    
    // create result background
    CCSprite* pSprite = CCSprite::create(cstResultBg);
    pSprite->setPosition(CUtility::GetWindowCenterPoint());
    this->addChild(pSprite, -1);
    
    return true;
}

void CResultLayer::setScoreData()
{
    m_iLineCount = 0;
    float fLabelPosX = 170;
    float fLabelPosY = CUtility::GetWindowSizeHeight() - 220;
    
    char textBuf[32] = {0};
    
    // get score info
    vector<ScoreInfo_t> vecScoreInfo;
    if(CUserData::sharedSettingData()->getScoreData(vecScoreInfo))
    {
        int iSize = vecScoreInfo.size();
        m_iLineCount = (iSize < cstLineMaxCnt)?(iSize):(cstLineMaxCnt);
        for (int i = 0; i < iSize; i++)
        {
            if(i>=cstLineMaxCnt)
            {
                break;
            }
            
            CCLabelTTF* pDateLabel = CCLabelTTF::create(vecScoreInfo[i].strDate.c_str(), "Thonburi", 36);
            pDateLabel->setPosition( ccp(fLabelPosX, fLabelPosY) );
            pDateLabel->setColor(ccBLACK);
            this->addChild(pDateLabel, 2);
            
            fLabelPosX += 220;
            
            for(int j = 0; j < cstScoreLblCnt; j++)
            {
                if(j == 0)
                    sprintf(textBuf, "%d", vecScoreInfo[i].iWin);
                else if(j == 1)
                    sprintf(textBuf, "%d", vecScoreInfo[i].iFail);
                else
                    sprintf(textBuf, "%d", vecScoreInfo[i].iDeuce);
                
                CCLabelTTF* pScoreLabel = CCLabelTTF::create(textBuf, "Thonburi", 36);
                pScoreLabel->setPosition( ccp(fLabelPosX, fLabelPosY) );
                pScoreLabel->setColor(ccBLACK);
                this->addChild(pScoreLabel, 2);
                
                fLabelPosX += 100;
            }
            
            fLabelPosX = 170;
            fLabelPosY -= 80;
        }
    }
}


void CResultLayer::draw()
{
    float height = CUtility::GetWindowSizeHeight();
    float width = CUtility::GetWindowSizeWidth();
    
    ccDrawColor4B(0,0,0,255);
    glLineWidth(1);
    
    float fStartPosY = height - 120;
    float fPosY = fStartPosY;
    ccDrawLine(ccp(0, fPosY),ccp(width, fPosY));
    
    fPosY -= 60;
    ccDrawLine(ccp(0, fPosY),ccp(width, fPosY));
    
    for(int i = 0; i < m_iLineCount; i++)
    {
        fPosY -= 80;
        ccDrawLine(ccp(0, fPosY),ccp(width, fPosY));
    }
    
    float fEndPosY = fPosY;
    
    ccDrawLine(ccp(340, fStartPosY), ccp(340, fEndPosY));
    ccDrawLine(ccp(440, fStartPosY), ccp(440, fEndPosY));
    ccDrawLine(ccp(540, fStartPosY), ccp(540, fEndPosY));
}

void CResultLayer::OnReturnMenu(cocos2d::CCObject* pSender)
{
    CCScene* pScene = CMenuLayer::scene();
    CCScene* transitionScene = CCTransitionMoveInL::create(0.5f, pScene);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
    if(CUserData::sharedSettingData()->getEffectMusicStatus())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(cstButtonEffect, false);
    }
}