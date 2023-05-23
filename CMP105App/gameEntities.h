#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class bonfireSprite : public GameObject {

public:
	bonfireSprite();
	~bonfireSprite();

	void update(float dt) override;

protected:
	Animation bonfire;
	Animation* currentBonfireAnimation;
};

class slimeCreature : public GameObject {

public:
	slimeCreature();
	~slimeCreature();

	void update(float dt) override;

	float moveSpeed;
	bool moveRight;
	float activeDisplacement;
	float finalDisplacement;

protected:
	Animation slimeMove;
	Animation* currentAnimation;
};