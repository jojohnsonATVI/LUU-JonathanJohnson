#pragma once
#include "Character.h"
class Player : public Character
{
	bool m_HasKey;

public:
	Player(float health, int x, int y);

	Player();
	
	void draw();

	void UseHealth(float health);

	void PickupKey(); 
};

