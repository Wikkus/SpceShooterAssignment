#include "enemyManager.h"

#include "enemyBase.h"
#include "enemyFighter.h"
#include "enemyWizard.h"
#include "gameEngine.h"

EnemyManager::EnemyManager() {
	_activeEnemies.reserve(10000);
}

EnemyManager::~EnemyManager() {}

void EnemyManager::Init() {
	for (unsigned i = 0; i < 5000; i++) {
		_inactiveEnemies.emplace_back(new EnemyFighter());
		_inactiveEnemies.back()->Init();
		_inactiveEnemies.emplace_back(new EnemyWizard());
		_inactiveEnemies.back()->Init();
	}
}

void EnemyManager::Update() {
	for (unsigned i = 0; i < _activeEnemies.size(); i++) {
		_activeEnemies[i]->Update();
	}
}

void EnemyManager::Render() {
	for (unsigned i = 0; i < _activeEnemies.size(); i++) {
		_activeEnemies[i]->Render();
	}
}

std::vector<EnemyBase*> EnemyManager::GetActiveEnemies() {
	return _activeEnemies;
}

void EnemyManager::CreateEnemy(EnemyType enemyType, float orientation,
	Vector2<float> direction, Vector2<float> position) {
	if (_inactiveEnemies.empty()) {
		_activeEnemies.emplace_back(new EnemyFighter());
		_activeEnemies.back()->Init();
		_activeEnemies.emplace_back(new EnemyWizard());
		_activeEnemies.back()->Init();
	} else {
		_activeEnemies.emplace_back(_inactiveEnemies.back());
		_activeEnemies.back()->ActivateEnemy(orientation, direction, position);
		_inactiveEnemies.pop_back();
	}

}

void EnemyManager::DeactivateAllEnemies() {
	while (_activeEnemies.size() > 0) {
		DeactivateEnemy(_activeEnemies.size() - 1);
	}
}

void EnemyManager::DeactivateEnemy(unsigned int enemyIndex) {
	_inactiveEnemies.emplace_back(_activeEnemies[enemyIndex]);
	_inactiveEnemies.back()->DeactivateEnemy();
	std::swap(_activeEnemies[enemyIndex], _activeEnemies.back());
	_activeEnemies.pop_back();
}

void EnemyManager::TakeDamage(unsigned int enemyIndex, unsigned int damageAmount) {
	//TakeDamage returns true if the enemy dies
	if(_inactiveEnemies[enemyIndex]->TakeDamage(damageAmount)) {
		DeactivateEnemy(enemyIndex);
	}
}
