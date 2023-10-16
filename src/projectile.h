#pragma once
#include "collision.h"
#include "sprite.h"
#include "vector2.h"

class Projectile {
public:
	Projectile(const char* spritePath, float collisionRadius, float projectileOrientation, 
		unsigned int projectileDamage, Vector2<float> projectileDirection, Vector2<float> projectilePosition);
	~Projectile();

	void Init();
	void Update();
	void Render();

	const Circle GetCollider() const;

	float GetOrientation(); 

	const unsigned int GetProjectileDamage() const;

	Sprite* GetSprite();

	Vector2<float> GetPosition();

private:
	Circle _circleCollider;

	const float _projectileSpeed = 200.f;
	const float _spriteCollisionOffset = 8.f;
	
	float _orientation = 0.f;

	unsigned int _projectileDamage;

	Sprite* _projectileSprite = nullptr;
	
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);
	Vector2<float> _position = Vector2<float>(0.f, 0.f);
};

