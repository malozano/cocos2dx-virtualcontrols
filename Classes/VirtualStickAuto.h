//
//  VirtualStickAuto.h
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 19/3/15.
//
//

#pragma once

#ifndef __Mario__VirtualStickAuto__
#define __Mario__VirtualStickAuto__

#include "GameEntity.h"
#include "cocos2d.h"
#include "VirtualControls.h"

#define kAUTOSTICK_MARGIN   20


class VirtualStickAuto: public VirtualControls {
public:
    
    bool init();    
    virtual void addTouchListeners(cocos2d::Node *node);

    CREATE_FUNC(VirtualStickAuto);
    
private:
    cocos2d::Sprite *m_buttonAction;
    cocos2d::Sprite *m_stickLeft;
    cocos2d::Sprite *m_stickLeftBase;
    
    cocos2d::Size m_radioStick;
    cocos2d::Point m_centerStick;    
};

#endif /* defined(__Mario__VirtualStickAuto__) */
