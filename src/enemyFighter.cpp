#include "enemyFighter.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "playerCharacter.h"
#include "timerManager.h"

EnemyFighter::EnemyFighter(const char* spritePath, int maxHealth, Vector2<float> position) : 
	EnemyBase(spritePath, maxHealth, position) {
	_sprite = new Sprite();
	_sprite->Load(spritePath);

	_position = position;

	_circleCollider.position = position;
	_circleCollider.radius = 16.f;

	_currentHealth = _maxHealth;
}

EnemyFighter::~EnemyFighter() {}

void EnemyFighter::Init() {
	_targetPosition = playerCharacter->GetPosition();
	_direction = _targetPosition - _position;

	_attackTimer =  timerManager->CreateTimer(1.f);
}

void EnemyFighter::Update() {
	UpdateTarget();
	if (!IsInDistance(_position, playerCharacter->GetPosition(), _attackRange * 0.5f)) {
		UpdateMovement();
	}
	UpdateAttack();
}

void EnemyFighter::Render() {
	_sprite->RenderWithOrientation(_position, _orientation);
}

const Circle EnemyFighter::GetCollider() const {
	return _circleCollider;
}

const float EnemyFighter::GetOrientation() const {
	return _orientation;
}

const int EnemyFighter::GetCurrentHealth() const {
	return _currentHealth;
}

const Sprite* EnemyFighter::GetSprite() const {
	return _sprite;
}

const Vector2<float> EnemyFighter::GetPosition() const {
	return _position;
}


bool EnemyFighter::TakeDamage(unsigned int damageAmount) {
	_currentHealth -= damageAmount;
	if (_currentHealth <= 0) {
		return true;
	}
	return false;
}

void EnemyFighter::UpdateAttack() {
	if (_attackTimer->GetTimerFinished()) {
		if (IsInDistance(_position, playerCharacter->GetPosition(), _attackRange)) {
			playerCharacter->TakeDamage(_attackDamage);
			_attackTimer->ResetTimer();
		}
	}
}

void EnemyFighter::UpdateMovement() {
	_direction = Vector2<float>(_targetPosition - _position).normalized();
	if (!IsInDistance(_position, playerCharacter->GetPosition(), _attackRange * 0.5f)) {
		_position += _direction * _movementSpeed * deltaTime;
		_circleCollider.position = _position;
	}
	_orientation = VectorAsOrientation(_direction);
}

void EnemyFighter::UpdateTarget() {
	_targetPosition = playerCharacter->GetPosition();
}