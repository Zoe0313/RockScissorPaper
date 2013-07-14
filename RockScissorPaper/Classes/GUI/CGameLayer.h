//
//  CGameLayer.h
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-6-27.
//
//

#ifndef __RockScissorPaper__CGameLayer__
#define __RockScissorPaper__CGameLayer__

#include "cocos2d.h"
const int cstHandBtnCnt = 3;
const int cstScoreLblCnt = 3;

class CGameLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static CGameLayer* create();
    
protected:
    virtual bool init();
    
private:
    void OnReturnMenu(cocos2d::CCObject* pSender);
    void OnClickButton(cocos2d::CCObject* pSender);
    void updateScore(int iUpIndex, int iDownIndex);
    void OnEnableAllButton();
    
private:
    cocos2d::CCMenuItemImage* m_pReturnItem;
    cocos2d::CCMenuItemImage* m_pHandItem[cstHandBtnCnt];
    
    cocos2d::CCSprite* m_UpSprite[cstHandBtnCnt];
    cocos2d::CCSprite* m_DownSprite[cstHandBtnCnt];
    cocos2d::CCPoint m_fUpHandPos[cstHandBtnCnt];
    cocos2d::CCPoint m_fDownHandPos[cstHandBtnCnt];
    
    int m_iScore[cstScoreLblCnt];
    cocos2d::CCLabelTTF* m_pNumberLabel[cstScoreLblCnt];
};

#endif /* defined(__RockScissorPaper__CGameLayer__) */
