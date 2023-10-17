#include "playerCharacter.h"

#include "dataStructuresAndMethods.h"
#include "debugDrawer.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "projectile.h"
#include "projectileManager.h"
#include "timerManager.h"

#include <string>

PlayerCharacter::PlayerCharacter(const char* spritePath, float characterOrientation, Vector2<float> characterPosition) {
	_characterSprite = new Sprite();	
	_characterSprite->Load(spritePath);

	_orientation = characterOrientation;
	_position = characterPosition;
	_oldPosition = _position;

	_currentHealth = _maxHealth;

	_circleCollider.position = characterPosition;
	_circleCollider.radius = 16.f;

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
	_attackTimer = timerManager->CreateTimer(0.5f);
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
	projectileManager->RemoveAllProjectiles();
}

void PlayerCharacter::FireProjectile() {
	projectileManager->CreateProjectile(new Projectile("res/sprites/FireBall.png", DamageType::DamageEnemy, _orientation, _attackDamage, _direction, _position));
}

void PlayerCharacter::UpdateInput() {
	if (_attackTimer->GetTimerFinished()) {
		if (GetMouseButton(SDL_BUTTON_LEFT)) {
			FireProjectile();
			_attackTimer->ResetTimer();
		}
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
	_circleCollider.position = _position;
	debugDrawer->AddDebugCircle(_position, _circleCollider.radius);
}

void PlayerCharacter::UpdateTarget() {
	_direction = GetMousePosition() - _position;
	_orientation = VectorAsOrientation(_direction);

}

const Circle PlayerCharacter::GetCircleCollider() const {
	return _circleCollider;
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
