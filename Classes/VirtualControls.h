//
//  VirtualControls.hpp
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 9/2/16.
//
//

#pragma once

#ifndef VirtualControls_hpp
#define VirtualControls_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

#define kNUM_BUTTONS    3
#define kNUM_AXIS    2

enum Button {
    BUTTON_ACTION=0,
    BUTTON_LEFT=1,
    BUTTON_RIGHT=2
};

enum Axis {
    AXIS_HORIZONTAL=0,
    AXIS_VERTICAL=1
};


class VirtualControls: public Node {
public:
    
    bool init();
    
    bool isButtonPressed(Button button);
    float getAxis(Axis axis);
    
    std::function<void(Button)> onButtonPressed;
    std::function<void(Button)> onButtonReleased;
    
    // Keyboard controls
    void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    void addKeyboardListeners(cocos2d::Node *node);
    virtual void addTouchListeners(cocos2d::Node *node);
        
    CREATE_FUNC(VirtualControls);
    
protected:

    bool buttonState[kNUM_BUTTONS];
    float axisState[kNUM_AXIS];
};


#endif /* VirtualControls_hpp */
