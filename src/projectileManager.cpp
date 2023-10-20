#include "projectileManager.h"

#include "dataStructuresAndMethods.h"
#include "enemyFighter.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "imGuiManager.h"
#include "playerCharacter.h"

ProjectileManager::ProjectileManager() {
	_activeEnemyProjectiles.reserve(10000);
	_activePlayerProjectiles.reserve(2000);
}

ProjectileManager::~ProjectileManager() {
	RemoveAllProjectiles();
	while (_inactiveEnemyProjectiles.size() > 0) {
		_inactiveEnemyProjectiles.back() = nullptr;
		delete _inactiveEnemyProjectiles.back();
		_inactiveEnemyProjectiles.pop_back();
	}
	while (_inactivePlayerProjectiles.size() > 0) {
		_inactivePlayerProjectiles.back() = nullptr;
		delete _inactivePlayerProjectiles.back();
		_inactivePlayerProjectiles.pop_back();
	}
}

void ProjectileManager::Init() {
	for (unsigned int i = 0; i < 20000; i++) {
		_inactiveEnemyProjectiles.emplace_back(new Projectile(DamageType::DamagePlayer));
		if (i <= 1000) {
			_inactivePlayerProjectiles.emplace_back(new Projectile(DamageType::DamageEnemy));		
		}
	}
}

void ProjectileManager::Update() {
	for (unsigned int i = 0; i < _activeEnemyProjectiles.size(); i++) {
		_activeEnemyProjectiles[i]->Update();
		if (CheckCollision(DamageType::DamagePlayer, i)) {
			continue;
		}
		if (OutOfBorderX(_activeEnemyProjectiles[i]->GetPosition().x) ||
			OutOfBorderY(_activeEnemyProjectiles[i]->GetPosition().y)) {
			RemoveProjectile(DamageType::DamagePlayer, i);
		}
	}
	for (unsigned int i = 0; i < _activePlayerProjectiles.size(); i++) {
		_activePlayerProjectiles[i]->Update();
		if (CheckCollision(DamageType::DamageEnemy, i)) {
			continue;
		}
		if (OutOfBorderX(_activePlayerProjectiles[i]->GetPosition().x) ||
			OutOfBorderY(_activePlayerProjectiles[i]->GetPosition().y)) {
			RemoveProjectile(DamageType::DamageEnemy, i);
		}
	}
}

void ProjectileManager::Render() {
	for (unsigned int i = 0; i < _activeEnemyProjectiles.size(); i++) {
		_activeEnemyProjectiles[i]->Render();
	}
	for (unsigned int i = 0; i < _activePlayerProjectiles.size(); i++) {
		_activePlayerProjectiles[i]->Render();
	}
}

void ProjectileManager::AddNewProjectile(DamageType damageType, float orientation, Vector2<float> direction, Vector2<float> position) {
	if (damageType == DamageType::DamageEnemy) {
		_activePlayerProjectiles.emplace_back(new Projectile(DamageType::DamagePlayer));
		_activePlayerProjectiles.back()->ActivateProjectile(orientation, direction, position);
	
	} else if (damageType == DamageType::DamagePlayer) {
		_activeEnemyProjectiles.emplace_back(new Projectile(DamageType::DamagePlayer));
		_activeEnemyProjectiles.back()->ActivateProjectile(orientation, direction, position);
	}
}

void ProjectileManager::SpawnProjectile(DamageType damageType, float orientation,
	Vector2<float> direction, Vector2<float> position) {
	if (damageType == DamageType::DamageEnemy) {
		if (_inactivePlayerProjectiles.empty()) {
			AddNewProjectile(damageType, orientation, direction, position);
		} else {
			_activePlayerProjectiles.emplace_back(_inactivePlayerProjectiles.back());
			_activePlayerProjectiles.back()->ActivateProjectile(orientation, direction, position);
			_inactivePlayerProjectiles.pop_back();
		}

	} else if (damageType == DamageType::DamagePlayer) {
		if (_inactiveEnemyProjectiles.empty()) {
			AddNewProjectile(damageType, orientation, direction, position);
		} else {
			_activeEnemyProjectiles.emplace_back(_inactiveEnemyProjectiles.back());
			_activeEnemyProjectiles.back()->ActivateProjectile(orientation, direction, position);
			_inactiveEnemyProjectiles.pop_back();
		}
	}
}

bool ProjectileManager::CheckCollision(DamageType damageType, unsigned int projectileIndex) {
	if (damageType == DamageType::DamageEnemy) {
		_currentCollider = _activePlayerProjectiles[projectileIndex]->GetCollider();
		for (unsigned int i = 0; i < enemyManager->GetActiveEnemies().size(); i++) {
			_intersectedCollider = enemyManager->GetActiveEnemies()[i]->GetCollider();
			if (CircleIntersect(_currentCollider, _intersectedCollider)) {
				if (enemyManager->GetActiveEnemies()[i]->TakeDamage(_activePlayerProjectiles[projectileIndex]->GetProjectileDamage())) {
					enemyManager->DeactivateEnemy(i);
				}
				RemoveProjectile(DamageType::DamageEnemy, projectileIndex);
				return true;
			}
		}
	} else if (damageType == DamageType::DamagePlayer) {
		_currentCollider = _activeEnemyProjectiles[projectileIndex]->GetCollider();
		_intersectedCollider = playerCharacter->GetCircleCollider();
		if (CircleIntersect(_currentCollider, _intersectedCollider)) {
			playerCharacter->TakeDamage(_activeEnemyProjectiles[projectileIndex]->GetProjectileDamage());
			RemoveProjectile(damageType, projectileIndex);
			return true;
		}
	}
	return false;
}

void ProjectileManager::RemoveAllProjectiles() {
	while (_activeEnemyProjectiles.size() > 0) {
		RemoveProjectile(DamageType::DamagePlayer, _activeEnemyProjectiles.size() - 1);
	}
	while (_activePlayerProjectiles.size() > 0) {
		RemoveProjectile(DamageType::DamageEnemy, _activePlayerProjectiles.size() - 1);
	}
}

void ProjectileManager::RemoveProjectile(DamageType damageType, unsigned int projectileIndex) {
	if (damageType == DamageType::DamagePlayer) {
		_activeEnemyProjectiles[projectileIndex]->DeactivateProjectile();
		std::swap(_activeEnemyProjectiles[projectileIndex], _activeEnemyProjectiles.back());
		_inactiveEnemyProjectiles.emplace_back(_activeEnemyProjectiles.back());
		_activeEnemyProjectiles.pop_back();
		

	} else if (damageType == DamageType::DamageEnemy) {
		_activePlayerProjectiles[projectileIndex]->DeactivateProjectile();
		std::swap(_activePlayerProjectiles[projectileIndex], _activePlayerProjectiles.back());
		_inactivePlayerProjectiles.emplace_back(_activePlayerProjectiles.back());	
		_activePlayerProjectiles.pop_back();	
	}
}