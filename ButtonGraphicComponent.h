#ifndef __BUTTON_GRAPHIC_COMPONENT_H__
#define __BUTTON_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"


class ButtonGraphicComponent : public GraphicComponent
{
public:
	ButtonGraphicComponent();
	~ButtonGraphicComponent();

	virtual void Update(Monster& hero, GameScene& scene);

	virtual int GetValue() const;
	virtual bool Winner() const;
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);
	virtual void ChangeCoins(int coins);
	virtual void ChangeHealth(int health);

	virtual void SetSpeedBullet(int speed);
	virtual int GetSpeedBullet() const;

	virtual void DescreaseQuentityBullet();
	virtual int  GetQuentityBullet() const;

	virtual void SetTargetPointForBullet(cocos2d::Point point);

	virtual void SetTargetPosition_YForHero(int target_y);

};

#endif 
