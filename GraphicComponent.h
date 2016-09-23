#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameScene;
class Monster;

// interface for other graphics classes
class GraphicComponent : public cocos2d::Sprite
{
public:
	virtual void Update(Monster& hero, GameScene& scene)	= 0;

	virtual int GetAttack() const = 0;
	virtual int GetHealth() const = 0;
	virtual std::string GetTypeObject() const = 0;
	virtual bool Dead(int wounded) = 0;

	virtual ~GraphicComponent() {};
};

#endif