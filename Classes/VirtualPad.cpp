//
//  VirtualPad.cpp
//  Mario
//
//  Created by Miguel Angel Lozano Ortega on 9/3/15.
//
//

#include "VirtualPad.h"

bool VirtualPad::init(){
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
    
    m_buttonLeft = Sprite::createWithSpriteFrameName("boton-direccion.png");
    m_buttonLeft->setAnchorPoint(Vec2(0,0));
    m_buttonLeft->setPosition(visibleOrigin.x+kPAD_MARGIN, visibleOrigin.y+kPAD_MARGIN);
    m_buttonLeft->setOpacity(127);
    m_buttonLeft->setTag(Button::BUTTON_LEFT);
    
    m_buttonRight = Sprite::createWithSpriteFrameName("boton-direccion.png");
    m_buttonRight->setAnchorPoint(Vec2(1,0));
    m_buttonRight->setScaleX(-1);
    m_buttonRight->setOpacity(127);
    m_buttonRight->setPosition(visibleOrigin.x+ kPAD_MARGIN + m_buttonLeft->getContentSize().width + kPAD_MARGIN, visibleOrigin.y+kPAD_MARGIN);
    m_buttonRight->setTag(Button::BUTTON_RIGHT);

    m_buttonAction = Sprite::createWithSpriteFrameName("boton-accion.png");
    m_buttonAction->setAnchorPoint(Vec2(1,0));
    m_buttonAction->setPosition(visibleOrigin.x + visibleSize.width - kPAD_MARGIN, visibleOrigin.y+kPAD_MARGIN);
    m_buttonAction->setOpacity(127);
    m_buttonAction->setTag(Button::BUTTON_ACTION);
    
    this->addChild(m_buttonLeft,0);
    this->addChild(m_buttonRight,0);
    this->addChild(m_buttonAction,0);
    this->setLocalZOrder(100);
    
    return true;
}


void VirtualPad::addTouchListeners(cocos2d::Node *node) {
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    
    m_listener->onTouchBegan = [=](Touch* touch, Event* event) {
        
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
    
    m_listener->onTouchEnded = [=](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(127);
        buttonState[target->getTag()] = false;
        if(onButtonReleased) {
            onButtonReleased((Button)target->getTag());
        }
    };
    
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_buttonLeft);
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener->clone(), m_buttonRight);
    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener->clone(), m_buttonAction);

}
