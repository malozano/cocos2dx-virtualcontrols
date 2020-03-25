//
//  VirtualStick.h
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 15/3/15.
//
//

#pragma once

#ifndef __Mario__VirtualStick__
#define __Mario__VirtualStick__

#include "GameEntity.h"
#include "cocos2d.h"
#include "VirtualControls.h"

#define kSTICK_MARGIN   20


class VirtualStick: public VirtualControls {
public:
    
    bool init();
    virtual void addTouchListeners(cocos2d::Node *node);
    
    CREATE_FUNC(VirtualStick);
    
private:
    cocos2d::Sprite *m_buttonAction;
    cocos2d::Sprite *m_stickLeft;
    cocos2d::Sprite *m_stickLeftBase;
    
    cocos2d::Size m_radioStick;
    cocos2d::Point m_centerStick;    
};
#endif /* defined(__Mario__VirtualStick__) */
