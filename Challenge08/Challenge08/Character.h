#pragma once
 class Character
{
protected: 
	float m_health;
	int m_xposition;
	int m_yposition;
	bool m_isAlive;

public:
	Character(float health, int x, int y);

	Character();

	virtual void draw();

	void Move(int x, int y);

	void TakeDamage(float damage);
 };

