#include "projectileManager.h"

#include "dataStructuresAndMethods.h"
#include "enemyFighter.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "imGuiManager.h"
#include "playerCharacter.h"
#include "quadTree.h"
ProjectileManager::ProjectileManager() {
	_activeEnemyProjectiles.reserve(10000);
	_activePlayerProjectiles.reserve(2500);
}

ProjectileManager::~ProjectileManager() {
	RemoveAllProjectiles();
}

void ProjectileManager::Init() {
	for (unsigned int i = 0; i < 10000; i++) {
		_inactiveEnemyProjectiles.emplace_back(new Projectile(DamageType::DamagePlayer, _latestProjectileID));
		_latestProjectileID += 4;
		if (i <= 2500) {
			_inactivePlayerProjectiles.emplace_back(new Projectile(DamageType::DamageEnemy, _latestProjectileID));
			_latestProjectileID += 4;
		}
	}
}

void ProjectileManager::Update() {
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
	for (unsigned int i = 0; i < _activeEnemyProjectiles.size(); i++) {
		_activeEnemyProjectiles[i]->Update();
		if (OutOfBorderX(_activeEnemyProjectiles[i]->GetPosition().x) ||
			OutOfBorderY(_activeEnemyProjectiles[i]->GetPosition().y)) {
			RemoveProjectile(DamageType::DamagePlayer, i);
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
		_activePlayerProjectiles.emplace_back(new Projectile(DamageType::DamageEnemy, _latestProjectileID));
		_activePlayerProjectiles.back()->ActivateProjectile(orientation, direction, position);
	
	} else if (damageType == DamageType::DamagePlayer) {
		_activeEnemyProjectiles.emplace_back(new Projectile(DamageType::DamagePlayer, _latestProjectileID));
		_activeEnemyProjectiles.back()->ActivateProjectile(orientation, direction, position);
	}
	_latestProjectileID += 4;
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
		std::vector<EnemyBase*> enemiesHit = enemyQuadTree->QueryTemp(_activePlayerProjectiles[projectileIndex]->GetCollider());
		for (unsigned int i = 0; i < enemiesHit.size(); i++) {
			if (enemiesHit[i]->TakeDamage(_activePlayerProjectiles[projectileIndex]->GetProjectileDamage())) {
				enemyManager->DeactivateEnemy(enemiesHit[i]->GetID());
			}
		}
		if (enemiesHit.size() > 0) {
			RemoveProjectile(DamageType::DamageEnemy, _activePlayerProjectiles[projectileIndex]->GetProjectileID());
			return true;
		}
	}
	return false;
}

void ProjectileManager::RemoveAllProjectiles() {
	while (_activeEnemyProjectiles.size() > 0) {
		RemoveProjectile(DamageType::DamagePlayer, _activeEnemyProjectiles.front()->GetProjectileID());
	}
	while (_activePlayerProjectiles.size() > 0) {
		RemoveProjectile(DamageType::DamageEnemy, _activePlayerProjectiles.front()->GetProjectileID());
	}
}

void ProjectileManager::RemoveProjectile(DamageType damageType, unsigned int projectileID) {
	if (damageType == DamageType::DamagePlayer) {
		for (unsigned int i = 0; i < _activeEnemyProjectiles.size(); i++) {
			if (_activeEnemyProjectiles[i]->GetProjectileID() == projectileID) {
				std::swap(_activeEnemyProjectiles[i], _activeEnemyProjectiles.back());
				_inactiveEnemyProjectiles.emplace_back(_activeEnemyProjectiles.back());
				_inactiveEnemyProjectiles.back()->DeactivateProjectile();
				_activeEnemyProjectiles.pop_back();
				break;
			}
		}
	} else if (damageType == DamageType::DamageEnemy) {
		for (unsigned int i = 0; i < _activePlayerProjectiles.size(); i++) {
			if (_activePlayerProjectiles[i]->GetProjectileID() == projectileID) {
				std::swap(_activePlayerProjectiles[i], _activePlayerProjectiles.back());
				_inactivePlayerProjectiles.emplace_back(_activePlayerProjectiles.back());
				_inactivePlayerProjectiles.back()->DeactivateProjectile();
				_activePlayerProjectiles.pop_back();
				break;
			}
		}
	}
}

std::vector<Projectile*> ProjectileManager::GetActiveProjectiles() {
	return _activePlayerProjectiles;
}

void ProjectileManager::UpdateQuadTree() {
	for (unsigned int i = 0; i < _activeEnemyProjectiles.size(); i++) {
		projectileQuadTree->InsertTemp(_activeEnemyProjectiles[i], _activeEnemyProjectiles[i]->GetCollider());
	}
}
