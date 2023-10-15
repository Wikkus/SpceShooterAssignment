#include "projectileManager.h"

#include <dataStructuresAndMethods.h>

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
