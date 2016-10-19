#include "BotInputComponent.h"
#include "Monster.h"
#include "GameObjectMonster.h"

BotInputComponent::BotInputComponent()
{

}

/*virtual*/ void BotInputComponent::Update(Monster& heroes)
{

}

BotInputComponent::~BotInputComponent()
{
	CCLOG("destructor botinput");
}
/*
	Tasks on 20:10:16:
	- create 4 levels for This game(can be different complexity!!!!!);
*/


/********** Different way for second Boys *******\(Try to go through)
	- goes on different side;
	- on their way add different obstacles but when user click (for example "jump" jumping second boys);
*/