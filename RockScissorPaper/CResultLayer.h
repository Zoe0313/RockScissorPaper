//
//  CResultLayer.h
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-2.
//
//

#ifndef __RockScissorPaper__CResultLayer__
#define __RockScissorPaper__CResultLayer__

#include "cocos2d.h"

class CResultLayer: public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static CResultLayer* create();

protected:
    virtual bool init();
    virtual void draw();

private:
    void OnReturnMenu(cocos2d::CCObject* pSender);
    void setScoreData();
    
private:
    int m_iLineCount;
};

#endif /* defined(__RockScissorPaper__CResultLayer__) */
