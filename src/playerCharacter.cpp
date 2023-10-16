#include "playerCharacter.h"

#include "dataStructuresAndMethods.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "projectile.h"
#include "projectileManager.h"

#include <string>

PlayerCharacter::PlayerCharacter(const char* spritePath, float characterOrientation, Vector2<float> characterPosition) {
	_characterSprite = new Sprite();	
	_characterSprite->Load(spritePath);

	_orientation = characterOrientation;
	_position = characterPosition;
	_oldPosition = _position;

	_currentHealth = _maxHealth;

	_healthTextSprite = new TextSprite();
	_healthTextSprite->SetPosition(Vector2<float>(windowWidth * 0.05f, windowHeight * 0.9f));
}

PlayerCharacter::~PlayerCharacter() {
	_characterSprite = nullptr;
	delete _characterSprite;

	_healthTextSprite = nullptr;
	delete _healthTextSprite;
}

void PlayerCharacter::Init() {
	_healthTextSprite->Init("res/roboto.ttf", 24, std::to_string(_currentHealth).c_str(), { 255, 255, 255, 255 });
}

void PlayerCharacter::Update() {
	UpdateInput();
	UpdateMovement();
	UpdateTarget();
}

void PlayerCharacter::Render() {
	_characterSprite->RenderWithOrientation(_position, _orientation);
}

void PlayerCharacter::RenderText() {
	_healthTextSprite->Render();
}

void PlayerCharacter::TakeDamage(unsigned int damageAmount) {
	_currentHealth -= damageAmount;
	
	_healthTextSprite->ChangeText(std::to_string(_currentHealth).c_str(), { 255, 255, 255, 255 });
	if (_currentHealth <= 0) {
		ExecuteDeath();
	}
}

void PlayerCharacter::ExecuteDeath() {
	_position = Vector2<float>(windowWidth * 0.5f, windowHeight * 0.5f);
	_orientation = 0.f;

	_currentHealth = _maxHealth;
	_healthTextSprite->ChangeText(std::to_string(_currentHealth).c_str(), { 255, 255, 255, 255 });

	enemyManager->RemoveAllEnemies();
}

void PlayerCharacter::FireProjectile() {
	projectileManager->CreateProjectile(new Projectile("res/sprites/FireBall.png", 8.f, _orientation, 10, _direction, _position));
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

const float PlayerCharacter::GetOrientation() const {
	return _orientation;
}

const int PlayerCharacter::GetCurrentHealth() const {
	return _currentHealth;
}

const Vector2<float> PlayerCharacter::GetPosition() const {
	return _position;
}
