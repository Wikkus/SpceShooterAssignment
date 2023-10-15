#include "playerCharacter.h"

#include "dataStructuresAndMethods.h"
#include "gameEngine.h"
#include "projectile.h"
#include "projectileManager.h"

PlayerCharacter::PlayerCharacter(const char* spritePath, float characterOrientation, Vector2<float> characterPosition) {
	_characterSprite = new Sprite();	
	_characterSprite->Load(spritePath);

	_orientation = characterOrientation;
	_position = characterPosition;
	_oldPosition = _position;
}

PlayerCharacter::~PlayerCharacter() {
	_characterSprite = nullptr;
	delete _characterSprite;
}

void PlayerCharacter::Init() {

}

void PlayerCharacter::Update() {
	UpdateInput();
	UpdateMovement();
	UpdateTarget();
}

void PlayerCharacter::Render() {
	_characterSprite->RenderWithOrientation(_position, _orientation);
}

void PlayerCharacter::FireProjectile() {
	Projectile* projectile = new Projectile("res/sprites/FireBall.png", 8.f, _orientation, _direction, _position);
	projectileManager->CreateProjectile(projectile);
}

void PlayerCharacter::UpdateInput() {
	if (_attackTimer <= 0.f) {
		if (GetMouseButton(SDL_BUTTON_LEFT)) {
			FireProjectile();
			_attackTimer = _attackCooldown;
		}
	}
	if (_attackTimer > 0.f) {
		_attackTimer -= deltaTime;
	}
}

void PlayerCharacter::UpdateMovement() {
	_oldPosition = _position;
	if (GetKey(SDL_SCANCODE_W)) {
		_position.y -= _movementSpeed * deltaTime;

	} else if (GetKey(SDL_SCANCODE_S)) {
		_position.y += _movementSpeed * deltaTime;
	}	
	
	if (GetKey(SDL_SCANCODE_A)) {
		_position.x -= _movementSpeed * deltaTime;

	} else if (GetKey(SDL_SCANCODE_D)) {
		_position.x += _movementSpeed * deltaTime;
	}

	if (OutOfBorderX(_position.x)) {
		_position.x = _oldPosition.x;
	}
	if (OutOfBorderY(_position.y)) {
		_position.y = _oldPosition.y;
	}
}

void PlayerCharacter::UpdateTarget() {
	_direction = GetMousePosition() - _position;
	_orientation = VectorAsOrientation(_direction);

}

Sprite* PlayerCharacter::GetSprite() {
	return _characterSprite;
}

float PlayerCharacter::GetOrientation() {
	return _orientation;
}

Vector2<float> PlayerCharacter::GetPosition() {
	return _position;
}
