#pragma once
#include "sprite.h"
#include "vector2.h"

class LesserEnemy {
public:
	LesserEnemy(const char* spritePath, float orientation, Vector2<float> position);
	~LesserEnemy();

	void Init();
	void Update();
	void Render();

	void UpdateMovement();
	void UpdateTarget();

	Sprite* GetSprite();

	float GetOrientation();
	Vector2<float> GetPosition();

private:
	const float _movementSpeed = 75.f;

	float _orientation = 0.f;

	Sprite* _sprite = nullptr;
	Vector2<float> _position = Vector2<float>(0.f, 0.f);
	Vector2<float> _targetPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);


};

