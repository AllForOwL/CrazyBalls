#include "Breed.h"

Breed::Breed(int attack, int health, string filename)
{
	m_attack = attack;
	m_health = health;
	m_filename = filename;
}

Breed::Breed(Breed& breed)
{
	this->m_attack	 = breed.GetAttack();
	this->m_health	 = breed.GetHealth();
	this->m_filename = breed.GetFileName();
}
int Breed::GetHealth()
{
	return m_health;
}

int Breed::GetAttack()
{
	return m_attack;
}

string Breed::GetFileName()
{
	return m_filename;
}
Breed::~Breed()
{
}
