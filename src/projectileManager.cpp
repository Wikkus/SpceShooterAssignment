#include "projectileManager.h"

#include "dataStructuresAndMethods.h"
#include "enemyFighter.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "playerCharacter.h"

ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() {
	for (unsigned int i = 0; i < _activeProjectiles.size(); i++) {
		RemoveProjectile(i);
	}
}

void ProjectileManager::Init() {
	for (unsigned int i = 0; i < _activeProjectiles.size(); i++) {
		_activeProjectiles[i]->Init();
	}
}

void ProjectileManager::Update() {
	for (unsigned int i = 0; i < _activeProjectiles.size(); i++) {
		_activeProjectiles[i]->Update();
		if (CheckCollision(i)) {
			continue;
		}
		if (OutOfBorderX(_activeProjectiles[i]->GetPosition().x) || 
			OutOfBorderY(_activeProjectiles[i]->GetPosition().y)) {
			RemoveProjectile(i);
		}
	}
}

void ProjectileManager::Render() {
	for (unsigned int i = 0; i < _activeProjectiles.size(); i++) {
		_activeProjectiles[i]->Render();
	}
}

void ProjectileManager::CreateProjectile(Projectile* projectile) {
	_activeProjectiles.emplace_back(projectile);
	projectile->Init();
}

bool ProjectileManager::CheckCollision(unsigned int projectileIndex) {
	_currentCollider = _activeProjectiles[projectileIndex]->GetCollider();
	if (_activeProjectiles[projectileIndex]->GetDamageType() == DamageType::DamagePlayer) {
		_intersectedCollider = playerCharacter->GetCircleCollider();
		if (CircleIntersect(_currentCollider, _intersectedCollider)) {
			playerCharacter->TakeDamage(_activeProjectiles[projectileIndex]->GetProjectileDamage());
			RemoveProjectile(projectileIndex);
			return true;
		}
	} else if (_activeProjectiles[projectileIndex]->GetDamageType() == DamageType::DamageEnemy) {
		for (unsigned int i = 0; i < enemyManager->GetAllEnemies().size(); i++) {
			_intersectedCollider = enemyManager->GetAllEnemies()[i]->GetCollider();
			if (CircleIntersect(_currentCollider, _intersectedCollider)) {
				if (enemyManager->GetAllEnemies()[i]->TakeDamage(_activeProjectiles[projectileIndex]->GetProjectileDamage())) {
					enemyManager->RemoveEnemy(i);
				}
				RemoveProjectile(projectileIndex);
				return true;
			}
		}
	}
	return false;
}

void ProjectileManager::RemoveAllProjectiles() {
	while (_activeProjectiles.size() > 0) {
		RemoveProjectile(_activeProjectiles.size() - 1);
	}
}

void ProjectileManager::RemoveProjectile(unsigned int projectileIndex) {
	_activeProjectiles[projectileIndex] = nullptr;
	delete _activeProjectiles[projectileIndex];
	std::swap(_activeProjectiles[projectileIndex], _activeProjectiles.back());
	_activeProjectiles.pop_back();
}
