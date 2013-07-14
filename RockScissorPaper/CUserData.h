//
//  CUserData.h
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-7-7.
//
//

#ifndef __RockScissorPaper__CUserData__
#define __RockScissorPaper__CUserData__

#include "cocos2d.h"

const int cstLineMaxCnt = 9;
typedef struct
{
    int iWin;
    int iFail;
    int iDeuce;
    std::string strDate;
} ScoreInfo_t;

class CUserData
{
public:
    static CUserData* sharedSettingData()
    {
        static CUserData* temp = NULL;
        if(temp == NULL)
        {
            temp = new CUserData();
        }
        return temp;
    }
    
    void setBgMusicStatus(bool bOpen);
    bool getBgMusicStatus();
    
    void setEffectMusicStatus(bool bOpen);
    bool getEffectMusicStatus();
    
    std::string getCurrentDate();
    
    void setScoreData(ScoreInfo_t info);
    bool getNewScoreData(ScoreInfo_t& info);
    bool getScoreData(std::vector<ScoreInfo_t>& vecInfo);
};

#endif /* defined(__RockScissorPaper__CUserData__) */
