#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Input.h"
#include "Map0.h"

class Player : public GameObject {

public:
	Player();
	~Player();

	void update(float dt, Input& input);
	void handleInput(float dt, Input& input);
	void collisionDetection(GameObject* collider, map0* tileMap);

protected:
	float speed;
	bool grounded;
	const float GRAVITY = 9.81f;
	bool isColliding;

	Animation idle;
	Animation run;
	Animation jump;
	Animation* currentAnimation;
};
