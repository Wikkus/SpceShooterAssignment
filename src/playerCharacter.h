#pragma once
#include "sprite.h"
#include "vector2.h"

class PlayerCharacter {
public:
	PlayerCharacter(const char* spritePath, float characterOrientation, Vector2<float> characterPosition);
	~PlayerCharacter();

	void Init();
	void Update();
	void Render();

	void FireProjectile();

	void UpdateInput();
	void UpdateMovement();
	void UpdateTarget();

	Sprite* GetSprite();

	float GetOrientation();	
	Vector2<float> GetPosition();

private:

	const float _attackCooldown = 0.5f;
	const float _movementSpeed = 100.f;

	float _attackTimer = 0.f;
	float _orientation = 0.f;

	Sprite* _characterSprite = nullptr;
	Vector2<float> _position = Vector2<float>(0.f, 0.f);
	Vector2<float> _oldPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);


};

