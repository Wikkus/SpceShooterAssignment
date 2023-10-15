#include "lesserEnemy.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "playerCharacter.h"

LesserEnemy::LesserEnemy(const char* spritePath, float orientation, Vector2<float> position) {
	_sprite = new Sprite();
	_sprite->Load(spritePath);

	_orientation = orientation;
	_position = position;

	_direction = _targetPosition - _position;
}

LesserEnemy::~LesserEnemy() {
	_sprite = nullptr;
	delete _sprite;
}

void LesserEnemy::Init() {}

void LesserEnemy::Update() {
	UpdateTarget();
	UpdateMovement();
}

void LesserEnemy::Render() {
	_sprite->RenderWithOrientation(_position, _orientation);
}

void LesserEnemy::UpdateMovement() {
	_direction = Vector2<float>(_targetPosition - _position).normalized();	
	_position += _direction * _movementSpeed * deltaTime;
	_orientation = VectorAsOrientation(_direction);
}

void LesserEnemy::UpdateTarget() {
	_targetPosition = playerCharacter->GetPosition();
}

Sprite* LesserEnemy::GetSprite() {
	return _sprite;
}

float LesserEnemy::GetOrientation() {
	return _orientation;
}

Vector2<float> LesserEnemy::GetPosition() {
	return _position;
}
