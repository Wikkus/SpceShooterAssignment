#pragma once
#include "textSprite.h"
#include "sprite.h"
#include "vector2.h"

class PlayerCharacter {
public:
	PlayerCharacter(const char* spritePath, float characterOrientation, Vector2<float> characterPosition);
	~PlayerCharacter();

	void Init();
	void Update();
	void Render();
	void RenderText();

	void ExecuteDeath();
	void FireProjectile();

	void TakeDamage(unsigned int damageAmount);

	void UpdateInput();
	void UpdateMovement();
	void UpdateTarget();

	Sprite* GetSprite();

	const float GetOrientation() const;	

	const int GetCurrentHealth() const;

	const Vector2<float> GetPosition() const;

private:
	const float _attackCooldown = 0.5f;
	const float _movementSpeed = 100.f;

	const int _maxHealth = 100;

	float _attackTimer = 0.f;
	float _orientation = 0.f;

	int _currentHealth = 0;

	Sprite* _characterSprite = nullptr;
	TextSprite* _healthTextSprite = nullptr;

	Vector2<float> _position = Vector2<float>(0.f, 0.f);
	Vector2<float> _oldPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);


};

