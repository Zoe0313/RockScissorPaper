#ifndef __CMENULAYER_H__
#define __CMENULAYER_H__

#include "cocos2d.h"

class CMenuLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static CMenuLayer* create();

protected:
    virtual bool init();
//    virtual void update(float delta);
//    virtual void onEnter();
//    virtual void onExit();
    
private:
    void menuCallback(CCObject* pSender);
};

#endif // __CMENULAYER_H__
