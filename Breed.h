#ifndef __BREED_H__
#define __BREED_H__

#include <string>

using namespace std;

class Breed
{
public:
	Breed(Breed& breed);

	Breed(int attack, int health, string filename);

	int GetHealth();
	int GetAttack();
	string GetFileName();

	~Breed();

private:
	int		m_attack;
	int		m_health;
	string m_filename;
};

#endif