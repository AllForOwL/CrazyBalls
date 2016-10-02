#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	// methods
	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(PauseScene);

	void GoToMainMenu(cocos2d::Ref* ref);
	void GoToGame(cocos2d::Ref* ref);

};

#endif // __MAIN_MENU_SCENE_H__
