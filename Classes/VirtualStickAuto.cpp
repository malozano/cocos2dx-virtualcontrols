//
//  VirtualStickAuto.cpp
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 19/3/15.
//
//

#include "VirtualStickAuto.h"

bool VirtualStickAuto::init(){
    if(!VirtualControls::init()) {
        return false;
    }

    //Cache de sprites
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    //Si no estaba el spritesheet en la caché lo cargo
    if(!spriteFrameCache->getSpriteFrameByName("boton-direccion.png")) {
        spriteFrameCache->addSpriteFramesWithFile("mando.plist");
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
     
    m_stickLeftBase = Sprite::createWithSpriteFrameName("base-stick.png");
    m_stickLeftBase->setAnchorPoint(Vec2(0.5,0.5));
    m_stickLeftBase->setVisible(false);
     
    m_stickLeft = Sprite::createWithSpriteFrameName("bola-stick.png");
    m_stickLeft->setAnchorPoint(Vec2(0.5,0.5));
    m_stickLeft->setVisible(false);
     
    m_radioStick = m_stickLeftBase->getContentSize() * 0.5 - m_stickLeft->getContentSize() * 0.5;
     
    m_buttonAction = Sprite::createWithSpriteFrameName("boton-accion.png");
    m_buttonAction->setAnchorPoint(Vec2(1,0));
    m_buttonAction->setOpacity(127);
    m_buttonAction->setPosition(visibleOrigin.x + visibleSize.width - kAUTOSTICK_MARGIN, visibleOrigin.y+kAUTOSTICK_MARGIN);
    m_buttonAction->setTag(Button::BUTTON_ACTION);
     
    this->addChild(m_stickLeftBase,0);
    this->addChild(m_stickLeft,1);
    this->addChild(m_buttonAction,0);
    this->setLocalZOrder(100);
    
    return true;
}

void VirtualStickAuto::addTouchListeners(cocos2d::Node *node) {
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if(rect.containsPoint(locationInNode)) {
            buttonState[target->getTag()] = true;
            if(onButtonPressed) {
                onButtonPressed((Button)target->getTag());
            }
            target->setOpacity(255);
            return true;
        }
        
        return false;
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(127);
        buttonState[target->getTag()] = false;
        if(onButtonReleased) {
            onButtonReleased((Button)target->getTag());
        }
    };
    
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_buttonAction);
    
    // Listener stick
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        m_centerStick = target->convertToNodeSpace(touch->getLocation());
        Size winSize = Director::getInstance()->getWinSize();
        
        if(m_centerStick.x < winSize.width/2) {
            m_stickLeftBase->setPosition(m_centerStick);
            m_stickLeftBase->setVisible(true);
            m_stickLeft->setPosition(m_centerStick);
            m_stickLeft->setVisible(true);
            
            return true;
        } else {
            return false;
        }
    };
    
    listener->onTouchMoved = [=](Touch* touch, Event* event) {
        Point offset = touch->getLocation()-touch->getStartLocation();
        
        Point max(m_radioStick);
        Point min(Point::ZERO-m_radioStick);
        offset.clamp(min, max);
        
        axisState[Axis::AXIS_VERTICAL] = offset.y / max.y;
        axisState[Axis::AXIS_HORIZONTAL] = offset.x / max.x;
        
        m_stickLeft->setPosition(m_centerStick + offset);
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        m_stickLeftBase->setVisible(false);
        m_stickLeft->setVisible(false);
        
        axisState[Axis::AXIS_VERTICAL] = 0;
        axisState[Axis::AXIS_HORIZONTAL] = 0;
    };
    
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
}
