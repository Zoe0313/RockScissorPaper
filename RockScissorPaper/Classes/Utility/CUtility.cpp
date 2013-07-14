//
//  CUtility.cpp
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-6-25.
//
//

#include "CUtility.h"

const float cstScreenMinWidth = 320.f;
const float cstScreenMinHeight = 480.f;

using namespace cocos2d;

CCSize CUtility::GetWindowSize()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return winSize;
}

float CUtility::GetWindowSizeWidth()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return winSize.width;
}

float CUtility::GetWindowSizeHeight()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return winSize.height;
}

CCPoint CUtility::GetWindowCenterPoint()
{
    CCPoint centerPos;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    centerPos.x = winSize.width/2;
    centerPos.y = winSize.height/2;
    return centerPos;
}

float CUtility::GetPicScaleFactor()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scaleWidth =  cstScreenMinWidth / winSize.width;
    float scaleHeight = cstScreenMinHeight / winSize.height;
    return (scaleWidth<scaleHeight?scaleWidth:scaleHeight);
}