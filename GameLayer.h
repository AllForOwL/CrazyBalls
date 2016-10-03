#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class Monster;

class GameLayer : public cocos2d::Layer
{
public:
	// methods
	virtual bool init();

	void Update(Monster& hero);

	void GoToPause(cocos2d::Ref* ref);

	CREATE_FUNC(GameLayer);

public:
	cocos2d::Label* m_lblAttackHero;
	cocos2d::Label* m_lblHealthHero;
	cocos2d::Label* m_lblCoinsHero;

	std::vector<std::string> m_vecNameSpritesWeapon;
	std::vector<std::string> m_vecNameSpritesBonus;
	std::vector<cocos2d::Sprite*> m_vecSpritesWeapon;
	std::vector<cocos2d::Sprite*> m_vecSpritesBonus;

	std::vector<cocos2d::Label*> m_vecLevelQuentityBullet;
	std::vector<int> m_IndexShowWeapon;

	int m_positionX;
};

#endif // __GAME_LAYER_H__
