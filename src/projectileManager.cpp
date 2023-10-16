#include "projectileManager.h"

#include "dataStructuresAndMethods.h"
#include "enemyManager.h"
#include "gameEngine.h"
#include "lesserEnemy.h"


ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() {
	for (unsigned int i = 0; i < _activeProjectiles.size(); i++) {
		_activeProjectiles[i] = nullptr;
		delete _activeProjectiles[i];
		std::swap(_activeProjectiles[i], _activeProjectiles.back());
		_activeProjectiles.pop_back();
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
		if (OutOfBorderX(_activeProjectiles[i]->GetPosition().x) || 
			OutOfBorderY(_activeProjectiles[i]->GetPosition().y)) {
			_activeProjectiles[i] = nullptr;
			delete _activeProjectiles[i];
			std::swap(_activeProjectiles[i], _activeProjectiles.back());
			_activeProjectiles.pop_back();
		}
	}
	CheckCollision();
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

void ProjectileManager::CheckCollision() {
	for (unsigned i = 0; i < enemyManager->GetEnemies().size(); i++) {
		_intersectedCollider = enemyManager->GetEnemies()[i]->GetCollider();

		for (unsigned int k = 0; k < _activeProjectiles.size(); k++) {
			_currentCollider = _activeProjectiles[k]->GetCollider();

			if (CircleIntersect(_currentCollider, _intersectedCollider)) {
				enemyManager->TakeDamage(i, _activeProjectiles[k]->GetProjectileDamage());
				RemoveProjectile(k);
			}
		}
	}
}

void ProjectileManager::RemoveProjectile(unsigned int projectileIndex) {
	_activeProjectiles[projectileIndex] = nullptr;
	delete _activeProjectiles[projectileIndex];
	std::swap(_activeProjectiles[projectileIndex], _activeProjectiles.back());
	_activeProjectiles.pop_back();

}
