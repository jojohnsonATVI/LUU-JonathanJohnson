#include "Character.h"
#include <iostream>

class Character
{
protected:
	float m_health;
	int m_xposition;
	int m_yposition;
	bool m_isAlive;
	
public:
	Character(float health, int x, int y)
		:m_health(health)
		, m_xposition(x)
		, m_yposition(y)
		, m_isAlive(true)
	{

	}
	Character()
		:m_health(1.f)
		, m_xposition(0)
		, m_yposition(0)
		, m_isAlive(true) 
	{
		
	}

	virtual void draw() {
		std::cout << "I'm not sure how to draw my self" << std::endl;
	}
	void Move(int x, int y)
	{
		m_xposition += x;
		m_yposition += y;
	}

	void TakeDamage(float damage)
	{
		if (m_isAlive) {
			m_health -= damage;
			if (m_health <= 0) {
				m_health = 0;
				m_isAlive = false;
			}
		}
	}
};
