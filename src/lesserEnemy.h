#pragma once
#include "collision.h"
#include "sprite.h"
#include "vector2.h"

class LesserEnemy {
public:
	LesserEnemy(const char* spritePath, float orientation, Vector2<float> position);
	~LesserEnemy();

	void Init();
	void Update();
	void Render();

	bool TakeDamage(unsigned int damageAmount);

	void UpdateAttack();
	void UpdateMovement();
	void UpdateTarget();

	const float GetOrientation() const;

	Circle GetCollider();

	const int GetCurrentHealth() const;

	const Sprite* GetSprite() const;

	const Vector2<float> GetPosition() const;

private:
	Circle _circleCollider;

	const float _attackRange = 25.f;
	const float _attackCooldown = 1.f;

	const float _movementSpeed = 75.f;

	const unsigned int _attackDamage = 5;
	
	const int _maxHealth = 30;

	float _attackTimer = 0.f;
	float _orientation = 0.f;

	int _currentHealth = 0.f;

	Sprite* _sprite = nullptr;
	Vector2<float> _position = Vector2<float>(0.f, 0.f);
	Vector2<float> _targetPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);


};

