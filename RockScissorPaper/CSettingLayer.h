//
//  CSettingLayer.h
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-2.
//
//

#ifndef __RockScissorPaper__CSettingLayer__
#define __RockScissorPaper__CSettingLayer__

#include "cocos2d.h"
const int cstSettingBtnCnt = 2;

class CSettingLayer:public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static CSettingLayer* create();
    
protected:
    virtual bool init();

private:
    CSettingLayer();
    
    void OnReturnMenu(cocos2d::CCObject* pSender);
    void OnClickButton(cocos2d::CCObject *menuItem);

private:
    cocos2d::CCLabelTTF* m_pControlLabel[cstSettingBtnCnt];
    cocos2d::CCMenuItemImage* m_returnButton;
    
    bool m_bOpenBgMusic;
    bool m_bOpenEffectMusic;
};
#endif /* defined(__RockScissorPaper__CSettingLayer__) */
