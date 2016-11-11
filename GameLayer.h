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
	
	std::string to_string(int i);

	void GoToPause(cocos2d::Ref* ref);

	CREATE_FUNC(GameLayer);

public:
	
	cocos2d::Sprite* m_menuBarBottom;

	cocos2d::Size m_visibleSize;

	cocos2d::Label* m_lblCoin;
	cocos2d::Label* m_lblPower;
	cocos2d::Label* m_lblPoint;

	std::vector<cocos2d::LabelTTF*>  m_veclblProperties;
	std::vector<cocos2d::Point>	  m_vecPointProperties;
};

#endif // __GAME_LAYER_H__
