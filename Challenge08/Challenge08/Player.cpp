#include "Player.h"
#include <iostream>
class Player : public Character {
	bool m_HasKey;
public:
	Player(float health, int x, int y)
		:Character(health, x, y)
		, m_HasKey(false)
	{

	}

	Player()
		:Character()
		, m_HasKey(false)

	{

	}

	void draw() override
	{
		std::cout << "@";
	}


	void UseHealth(float health)
	{
		m_health += health;
		if (!m_isAlive) {
			m_isAlive = true;
		}
	}

	void PickupKey()
	{
		m_HasKey = true;
	}
};