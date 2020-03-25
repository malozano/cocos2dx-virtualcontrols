# Virtual Controls for Cocos2d-x

This project provides a Cocos2d-x node subclass to add different kinds of virtual controls to your game:

* Virtual Pad (digital)
* Virtual Stick (analogic, fixed position)
* Virtual Stick (analogic, self-positioned)

## Usage

* Add all the content of the `Classes` folder to the `Classes` folder of your Cocos2d-x project.
* The the proper resources to the `Resourcesp` folder of your Cocos2d-x project (you may either choose the SD or HD version, depending on your game target resolution)
* Add a virtual controls node to your scene, and register its touch listeners:

```
auto controls = VirtualStick::create();
addChild(controls);
controls->addTouchListeners(this);
```
