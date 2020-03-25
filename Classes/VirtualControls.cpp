//
//  VirtualControls.cpp
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 9/2/16.
//
//

#include "VirtualControls.h"



bool VirtualControls::init(){
    if(!Node::init()) {
        return false;
    }
    
    for(int i=0;i<kNUM_BUTTONS;i++) {
        buttonState[i] = false;
    }
    
    for(int i=0;i<kNUM_AXIS;i++) {
        axisState[i] = 0.0f;
    }
    
    return true;
}

bool VirtualControls::isButtonPressed(Button button) {
    return buttonState[button];
}

float VirtualControls::getAxis(Axis axis) {
    return clampf(axisState[axis], -1.0, 1.0);
}

// Keyboard input support

void VirtualControls::addKeyboardListeners(cocos2d::Node *node) {
    //Creo listeners del teclado
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(VirtualControls::onKeyPressed,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
    
    listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(VirtualControls::onKeyReleased,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void VirtualControls::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    
    if(onButtonPressed) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
        {
            onButtonPressed(Button::BUTTON_LEFT);
            axisState[Axis::AXIS_HORIZONTAL] -= 1.0;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
        {
            onButtonPressed(Button::BUTTON_RIGHT);
            axisState[Axis::AXIS_HORIZONTAL] += 1.0;
        }
        else if(keyCode==EventKeyboard::KeyCode::KEY_SPACE)
        {
            onButtonPressed(Button::BUTTON_ACTION);
        }
    }
    
}

void VirtualControls::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    
    if(onButtonReleased) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
        {
            onButtonReleased(Button::BUTTON_LEFT);
            axisState[Axis::AXIS_HORIZONTAL] += 1.0;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
        {
            onButtonReleased(Button::BUTTON_RIGHT);
            axisState[Axis::AXIS_HORIZONTAL] -= 1.0;
        }
        else if(keyCode==EventKeyboard::KeyCode::KEY_SPACE)
        {
            onButtonReleased(Button::BUTTON_ACTION);
        }
    }
    
}

void VirtualControls::addTouchListeners(cocos2d::Node *node) {
    
}
