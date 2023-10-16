#include "lesserEnemy.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "playerCharacter.h"

LesserEnemy::LesserEnemy(const char* spritePath, float orientation, Vector2<float> position) {
	_sprite = new Sprite();
	_sprite->Load(spritePath);

	_orientation = orientation;
	_position = position;

	_circleCollider.position = position;
	_circleCollider.radius = 16.f;

	_direction = _targetPosition - _position;

	_currentHealth = _maxHealth;
}

LesserEnemy::~LesserEnemy() {
	_sprite = nullptr;
	delete _sprite;
}

void LesserEnemy::Init() {}

void LesserEnemy::Update() {
	UpdateTarget();
	if (!IsInDistance(_position, playerCharacter->GetPosition(), 20.f)) {
		UpdateMovement();
	}
	UpdateAttack();
}

void LesserEnemy::Render() {
	_sprite->RenderWithOrientation(_position, _orientation);
}

bool LesserEnemy::TakeDamage(unsigned int damageAmount) {
	_currentHealth -= damageAmount;
	if (_currentHealth <= 0) {
		return true;
	}
	return false;
}

void LesserEnemy::UpdateAttack() {
	if (_attackTimer >= 0) {
		_attackTimer -= deltaTime;
	} else {
		if (IsInDistance(_position, playerCharacter->GetPosition(), _attackRange)) {
			playerCharacter->TakeDamage(_attackDamage);
			_attackTimer = _attackCooldown;
		}
	}
}

void LesserEnemy::UpdateMovement() {
	_direction = Vector2<float>(_targetPosition - _position).normalized();	
	_position += _direction * _movementSpeed * deltaTime;
	_orientation = VectorAsOrientation(_direction);

	_circleCollider.position = _position;
}

void LesserEnemy::UpdateTarget() {
	_targetPosition = playerCharacter->GetPosition();
}

const Sprite* LesserEnemy::GetSprite() const {
	return _sprite;
}

const float LesserEnemy::GetOrientation() const {
	return _orientation;
}

Circle LesserEnemy::GetCollider() {
	return _circleCollider;
}

const int LesserEnemy::GetCurrentHealth() const {
	return _currentHealth;
}

const Vector2<float> LesserEnemy::GetPosition() const {
	return _position;
}
