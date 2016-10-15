#include "AirplaneEnemyGraphicComponent.h"

AirplaneEnemyGraphicComponent::AirplaneEnemyGraphicComponent(int i_attack, int i_armor,int i_health, const std::string& i_typeObject)
																:	m_attack(i_attack),
																	m_armor(i_armor),
																	m_health(i_health),
																	m_typeObject(i_typeObject)
{
}

AirplaneEnemyGraphicComponent::AirplaneEnemyGraphicComponent(const AirplaneEnemyGraphicComponent& copyObject)
{
	this->m_attack		= copyObject.m_attack;
	this->m_armor		= copyObject.m_armor;
	this->m_health		= copyObject.m_health;
	this->m_typeObject	= copyObject.m_typeObject;




}

void AirplaneEnemyGraphicComponent::SetPropertiesAirplane()
{

}
