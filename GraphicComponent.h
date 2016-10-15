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
	virtual void Update(Monster& hero, GameScene& scene)  = 0;
	virtual ~GraphicComponent() {};

	virtual std::string GetTypeObject()const
	{
		return std::string("");
	}

	virtual int	GetValue() const
	{
		return 1;
	}
	virtual int	GetAttack()	const
	{
		return 1;
	}
	virtual int	GetHealth() const
	{
		return 1;
	}
	virtual bool Dead(int wounded)
	{
		return true;
	}
	virtual void ChangeCoins(int coins)
	{

	}
	virtual void ChangeHealth(int health)
	{

	}
	virtual bool Winner() const
	{
		return true;
	}
	virtual void SetSpeedBullet(int speed)
	{

	}
	virtual int	GetSpeedBullet() const
	{
		return 1;
	}
	virtual void DescreaseQuentityBullet()
	{

	}
	virtual int	GetQuentityBullet()	const
	{
		return 1;
	}
	virtual void SetTargetPointForBullet(cocos2d::Point point)
	{

	}
	virtual void SetTargetPosition_YForHero(int target_y)
	{

	}
	virtual void HideObject()
	{

	}
	virtual void StartShowAnimation()
	{

	}
	virtual std::string& GetFileName()
	{
		return std::string(" ");
	}
	virtual int GetArmor() const
	{
		return 1;
	}
	virtual int GetID() const
	{
		return 1;
	}

};

#endif