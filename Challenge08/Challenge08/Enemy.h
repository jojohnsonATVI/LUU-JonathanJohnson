#pragma once
#include "Character.h"
class Enemy : public Character
{
	float m_Strength;

public:
	Enemy(float health, int x, int y, float strength);

	Enemy();

	void draw() override;
};

