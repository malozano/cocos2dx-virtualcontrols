//
//  VirtualPad.h
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 9/3/15.
//
//

#pragma once

#ifndef __Mario__VirtualPad__
#define __Mario__VirtualPad__

#include "GameEntity.h"
#include "cocos2d.h"
#include "VirtualControls.h"

#define kPAD_MARGIN   20


class VirtualPad: public VirtualControls {
public:
    
    bool init();
    virtual void addTouchListeners(cocos2d::Node *node);

    CREATE_FUNC(VirtualPad);
    
private:
    cocos2d::Sprite *m_buttonAction;
    cocos2d::Sprite *m_buttonLeft;
    cocos2d::Sprite *m_buttonRight;
    
    cocos2d::EventListenerTouchOneByOne *m_listener;
};
#endif /* defined(__Mario__VirtualPad__) */
