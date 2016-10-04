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

	void ShowAnimation(float dt);

	void GoToPause(cocos2d::Ref* ref);
	void ShowQuentityBullet(int tagWeapon, int quentityBullet);

	void LoadSpritesName();

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

	cocos2d::Sprite* m_animationPower;
	cocos2d::Sprite* m_animationCoin;

	std::vector<std::string> m_vecNameSpritesAnimationPower;
	std::vector<std::string> m_vecNameSpritesAnimationCoin;

	std::string m_typeAnimation;

	int m_indexInVectorAnimation;

};

#endif // __GAME_LAYER_H__
