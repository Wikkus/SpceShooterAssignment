#pragma once
#include "collision.h"
#include "sprite.h"
#include "vector2.h"

class Timer;

class EnemyBase {
public:
	EnemyBase(const char* spritePath, int maxHealth, Vector2<float> position) : _maxHealth(maxHealth) {}
	~EnemyBase() {}


	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool TakeDamage(unsigned int damageAmount) = 0;

	virtual const Circle GetCollider() const = 0;
	virtual const float GetOrientation() const = 0;
	virtual const int GetCurrentHealth() const = 0;
	virtual const Sprite* GetSprite() const = 0;
	virtual const Vector2<float> GetPosition() const = 0;

protected:
	Circle _circleCollider;

	const int _maxHealth;

	float _orientation = 0.f;
	
	int _currentHealth = 0.f;

	Sprite* _sprite = nullptr;

	Timer* _attackTimer = nullptr;

	Vector2<float> _position = Vector2<float>(0.f, 0.f);
	Vector2<float> _targetPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);

};

