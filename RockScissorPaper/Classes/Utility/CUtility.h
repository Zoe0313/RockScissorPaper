//
//  CUtility.h
//  RockScissorPaper
//
//  Created by 刘 晓霞 on 13-6-25.
//
//

#ifndef __RockScissorPaper__CUtility__
#define __RockScissorPaper__CUtility__
#include "cocos2d.h"
class CUtility
{
public:
    
    // Screen Helper Function 
    static cocos2d::CCSize GetWindowSize();
    static float GetWindowSizeWidth();
    static float GetWindowSizeHeight();
    static cocos2d::CCPoint GetWindowCenterPoint();
    static float GetPicScaleFactor();
};

#endif /* defined(__RockScissorPaper__CUtility__) */
