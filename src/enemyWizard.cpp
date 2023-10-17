#include "enemyWizard.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "playerCharacter.h"
#include "projectileManager.h"
#include "timerManager.h"

EnemyWizard::EnemyWizard(const char* spritePath, int maxHealth, Vector2<float> position) :
	EnemyBase(spritePath, maxHealth, position) {
	_sprite = new Sprite();
	_sprite->Load(spritePath);

	_position = position;

	_circleCollider.position = position;
	_circleCollider.radius = 16.f;

	_currentHealth = _maxHealth;
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


bool EnemyWizard::TakeDamage(unsigned int damageAmount) {
	_currentHealth -= damageAmount;
	if (_currentHealth <= 0) {
		return true;
	}
	return false;
}

void EnemyWizard::UpdateAttack() {
	if (IsInDistance(_position, playerCharacter->GetPosition(), _attackRange)) {
		projectileManager->CreateProjectile(new Projectile("res/sprites/Arcaneball.png", DamageType::DamagePlayer, _orientation, _attackDamage, _direction, _position));
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