#include "enemyWizard.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "playerCharacter.h"
#include "projectileManager.h"
#include "timerManager.h"

EnemyWizard::EnemyWizard() {
	_sprite = new Sprite();
	_sprite->Load("res/sprites/CoralineDadWizard.png");

	_position = Vector2<float>(-10000.f, -10000.f);

	_circleCollider.position = _position;
	_circleCollider.radius = 16.f;
	
	_maxHealth = 20;
	_currentHealth = _maxHealth;
	_enemyType = EnemyType::EnemyWizard;
}

EnemyWizard::~EnemyWizard() {}

void EnemyWizard::Init() {
	_targetPosition = playerCharacter->GetPosition();
	_direction = Vector2<float>(_targetPosition - _position).normalized();

	_orientation = VectorAsOrientation(_direction);

	_attackTimer = timerManager->CreateTimer(1.f);
}

void EnemyWizard::Update() {
	UpdateTarget();
	UpdateMovement();

	if (_attackTimer->GetTimerFinished()) {
		UpdateAttack();
	}
}

void EnemyWizard::Render() {
	_sprite->RenderWithOrientation(_position, _orientation);
}

const Circle EnemyWizard::GetCollider() const {
	return _circleCollider;
}

const EnemyType EnemyWizard::GetEnemyType() const {
	return _enemyType;
}

const float EnemyWizard::GetOrientation() const {
	return _orientation;
}

const int EnemyWizard::GetCurrentHealth() const {
	return _currentHealth;
}

const Sprite* EnemyWizard::GetSprite() const {
	return _sprite;
}

const Vector2<float> EnemyWizard::GetPosition() const {
	return _position;
}

void EnemyWizard::ActivateEnemy(float orienation, Vector2<float> direction, Vector2<float> position) {
	_orientation = orienation;
	_direction = direction;
	_position = position;
	_circleCollider.position = position;
}

void EnemyWizard::DeactivateEnemy() {
	_orientation = 0.f;
	_direction = Vector2<float>(0.f, 0.f);
	_position = Vector2<float>(-10000.f, -10000.f);
	_circleCollider.position = _position;
}

bool EnemyWizard::TakeDamage(unsigned int damageAmount) {
	_currentHealth -= damageAmount;
	if (_currentHealth <= 0) {
		return true;
	}
	return false;
}

void EnemyWizard::UpdateAttack() {
	if (IsInDistance(_position, playerCharacter->GetPosition(), _attackRange)) {
		projectileManager->SpawnProjectile(DamageType::DamagePlayer, _orientation, _direction, _position);
		_attackTimer->ResetTimer();
	}
}

void EnemyWizard::UpdateMovement() {
	_direction = Vector2<float>(_targetPosition - _position).normalized();
	if (!IsInDistance(_position, playerCharacter->GetPosition(), _attackRange * 0.5f)) {
		_position += _direction * _movementSpeed * deltaTime;
		_circleCollider.position = _position;
	}
	_orientation = VectorAsOrientation(_direction);
}

void EnemyWizard::UpdateTarget() {
	_targetPosition = playerCharacter->GetPosition();
}