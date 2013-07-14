//
//  CUserData.cpp
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-7.
//
//

#include "CUserData.h"
using namespace cocos2d;
using namespace std;

#define kBgMusicStatusKey "BgMusicStatus"
#define kEffectMusicStatusKey "EffectMusicStatus"

#define kDateKey "date%d"
#define kWinKey "win%d"
#define kFailKey "fail%d"
#define kDeuceKey "deuce%d"

void CUserData::setBgMusicStatus(bool bOpen)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(kBgMusicStatusKey, bOpen);
    CCUserDefault::sharedUserDefault()->flush();
}

bool CUserData::getBgMusicStatus()
{
    bool bOpen = CCUserDefault::sharedUserDefault()->getBoolForKey(kBgMusicStatusKey);

    return bOpen;
}

void CUserData::setEffectMusicStatus(bool bOpen)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(kEffectMusicStatusKey, bOpen);
    CCUserDefault::sharedUserDefault()->flush();
}

bool CUserData::getEffectMusicStatus()
{
    bool bOpen = CCUserDefault::sharedUserDefault()->getBoolForKey(kEffectMusicStatusKey);
    
    return bOpen;
}

string CUserData::getCurrentDate()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    struct tm *tm;
    tm = localtime(&now.tv_sec);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    
    char textBuf[32] = {0};
    sprintf(textBuf, "%d/%d/%d", year, month, day);
    
    string dateInfo = string(textBuf);
    
    return dateInfo;
}

void CUserData::setScoreData(ScoreInfo_t info)
{
    vector<ScoreInfo_t> vecInfo;
    bool bRet = getScoreData(vecInfo);
    char textBuf[32] = {0};
    if(bRet)
    {
        int index = 0;
        vector<ScoreInfo_t>::const_iterator iter = vecInfo.begin();
        for (; iter != vecInfo.end(); iter++, index++)
        {
            if(index >= cstLineMaxCnt)
            {
                break;
            }
            
            if(0 == index && getCurrentDate() == iter->strDate)
            {
                sprintf(textBuf, kWinKey, 0);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iWin);
                
                sprintf(textBuf, kFailKey, 0);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iFail);
                
                sprintf(textBuf, kDeuceKey, 0);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iDeuce);
            }
            else
            {
                sprintf(textBuf, kDateKey, index);
                CCUserDefault::sharedUserDefault()->setStringForKey(textBuf, iter->strDate);
                
                sprintf(textBuf, kWinKey, index);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, iter->iWin);
                
                sprintf(textBuf, kFailKey, index);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, iter->iFail);
                
                sprintf(textBuf, kDeuceKey, index);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, iter->iDeuce);
            }
        }
        
        CCUserDefault::sharedUserDefault()->flush();
    }
    else
    {
        sprintf(textBuf, kDateKey, 0);
        CCUserDefault::sharedUserDefault()->setStringForKey(textBuf, info.strDate);
        
        sprintf(textBuf, kWinKey, 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iWin);
        
        sprintf(textBuf, kFailKey, 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iFail);
        
        sprintf(textBuf, kDeuceKey, 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(textBuf, info.iDeuce);
        
        CCUserDefault::sharedUserDefault()->flush();
    }
}

bool CUserData::getNewScoreData(ScoreInfo_t& info)
{
    char textBuf[32] = {0};
    sprintf(textBuf, kDateKey, 0);
    
    string strDate = CCUserDefault::sharedUserDefault()->getStringForKey(textBuf,"");
    if(strDate.empty())
    {
        return false;
    }
    
    sprintf(textBuf, kWinKey, 0);
    int iWin = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
    
    sprintf(textBuf, kFailKey, 0);
    int iFail = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
    
    sprintf(textBuf, kDeuceKey, 0);
    int iDeuce = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
    
    info.strDate = strDate;
    info.iWin = iWin;
    info.iFail = iFail;
    info.iDeuce = iDeuce;
    
    return true;
}

bool CUserData::getScoreData(vector<ScoreInfo_t>& vecInfo)
{
    vecInfo.clear();
    
    char textBuf[32] = {0};
    ScoreInfo_t scoreInfo;
    
    for(int i = 0; i < cstLineMaxCnt; i++)
    {
        sprintf(textBuf, kDateKey, i);
        string strDate = CCUserDefault::sharedUserDefault()->getStringForKey(textBuf,"");
        if(strDate.empty())
        {
            break;
        }
        
        sprintf(textBuf, kWinKey, i);
        int iWin = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
        
        sprintf(textBuf, kFailKey, i);
        int iFail = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
        
        sprintf(textBuf, kDeuceKey, i);
        int iDeuce = CCUserDefault::sharedUserDefault()->getIntegerForKey(textBuf, 0);
        
        scoreInfo.strDate = strDate;
        scoreInfo.iWin = iWin;
        scoreInfo.iFail = iFail;
        scoreInfo.iDeuce = iDeuce;
        
        vecInfo.push_back(scoreInfo);
    }
    if(vecInfo.empty())
    {
        return false;
    }
    
    return true;
}


