#include "projectile.h"

#include "debugDrawer.h"
#include "gameEngine.h"

Projectile::Projectile(const char* spritePath, float collisionRadius, float projectileOrientation,
	Vector2<float> projectileDirection, Vector2<float> projectilePosition) {
	_projectileSprite = new Sprite();
	_projectileSprite->Load(spritePath);

	_orientation = projectileOrientation;

	_direction = projectileDirection.normalized();
	_position = projectilePosition;

	_circleCollider.radius = collisionRadius;
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

Sprite* Projectile::GetSprite() {
	return _projectileSprite;
}

float Projectile::GetOrientation() {
	return _orientation;
}

Vector2<float> Projectile::GetPosition() {
	return _position;
}