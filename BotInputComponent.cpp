#include "BotInputComponent.h"
#include "Monster.h"
#include "GameObjectMonster.h"
#include "Monster.h"
#include "AirplaneEnemyGraphicComponent.h"

BotInputComponent::BotInputComponent()
{

}

/*virtual*/ void BotInputComponent::Update(Monster& heroes)
{
	if (heroes.m_objectMonster->m_vecComponentEnemyAirplane.size())
	{
		int _positionYHero = heroes.m_graphicComponentHero->getPositionY();
	
		for (int i = 0; i < heroes.m_objectMonster->m_vecComponentEnemyAirplane.size(); i++)
		{
			int _positionYAirplane = heroes.m_objectMonster->m_vecComponentEnemyAirplane[i]->getPositionY();
			if (_positionYAirplane > _positionYHero)
			{
				heroes.m_objectMonster->m_vecComponentEnemyAirplane[i]->m_stateAirplane = AirplaneEnemyGraphicComponent::StateAirplane::STATE_MOVE_DOWN;
			}
			else
			{
				heroes.m_objectMonster->m_vecComponentEnemyAirplane[i]->m_stateAirplane = AirplaneEnemyGraphicComponent::StateAirplane::STATE_MOVE_UP;
			}
		}
	}
}

BotInputComponent::~BotInputComponent()
{
	CCLOG("destructor botinput");
}
/*
	Tasks on 20:10:16:
	+ create 4 levels for This game(can be different complexity!!!!!);
*/


/********** Different way for second Boys *******\(Try to go through)
	- goes on different side;
	- on their way add different obstacles but when user click (for example "jump" jumping second boys);
*/