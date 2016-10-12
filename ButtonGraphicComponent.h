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
};

#endif 
