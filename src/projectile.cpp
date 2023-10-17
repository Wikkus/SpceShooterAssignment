#include "projectile.h"

#include "debugDrawer.h"
#include "enemyFighter.h"
#include "enemyManager.h"
#include "gameEngine.h"

Projectile::Projectile(const char* spritePath, DamageType damageType, float projectileOrientation,
	unsigned int projectileDamage, Vector2<float> projectileDirection, Vector2<float> projectilePosition) {
	_projectileSprite = new Sprite();
	_projectileSprite->Load(spritePath);

	_orientation = projectileOrientation;

	_projectileDamage = projectileDamage;

	_direction = projectileDirection.normalized();
	_position = projectilePosition;

	_damageType = damageType;

	_circleCollider.radius = 8.f;
	_circleCollider.position = projectilePosition + _direction * _projectileSprite->h * 0.5f;
}

Projectile::~Projectile() {}

void Projectile::Init() {}

void Projectile::Update() {
	_position += _direction * _projectileSpeed * deltaTime;
	_circleCollider.position = _position + _direction * (_projectileSprite->h * 0.25f);
}

void Projectile::Render() {
	_projectileSprite->RenderWithOrientation(_position, _orientation);
}

const Circle Projectile::GetCollider() const {
	return _circleCollider;
}

const DamageType Projectile::GetDamageType() const {
	return _damageType;
}

Sprite* Projectile::GetSprite() {
	return _projectileSprite;
}

float Projectile::GetOrientation() {
	return _orientation;
}

const unsigned int Projectile::GetProjectileDamage() const {
	return _projectileDamage;
}

Vector2<float> Projectile::GetPosition() {
	return _position;
}
