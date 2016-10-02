#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	// methods
	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(GameOverScene);

	void GoToMainMenu(cocos2d::Ref* ref);
	void Exit(cocos2d::Ref* ref);

};

#endif // __MAIN_MENU_SCENE_H__
