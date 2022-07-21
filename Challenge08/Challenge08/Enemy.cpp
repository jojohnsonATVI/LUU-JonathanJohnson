#include "Enemy.h"
#include <iostream>
class Enemy : public Character {

	float m_Strength;

public:
	Enemy(float health, int x, int y, float strength)
		:Character(health, x, y)
		, m_Strength(strength)
	{

	}
	Enemy()
		:Character()
		, m_Strength(0)
	{

	}

	void draw() override
	{
		std::cout << "*";
	}
};
