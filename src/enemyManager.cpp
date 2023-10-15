#include "enemyManager.h"

#include "lesserEnemy.h"

EnemyManager::EnemyManager() {}

EnemyManager::~EnemyManager() {
	for (unsigned int i = 0; i < _lesserEnemies.size(); i++) {
		_lesserEnemies[i] = nullptr;
		delete _lesserEnemies[i];
		std::swap(_lesserEnemies[i], _lesserEnemies.back());
		_lesserEnemies.pop_back();
	}
}

void EnemyManager::Init() {
	for (unsigned int i = 0; i < _lesserEnemies.size(); i++) {
		_lesserEnemies[i]->Init();
	}
}

void EnemyManager::Update() {
	for (unsigned int i = 0; i < _lesserEnemies.size(); i++) {
		_lesserEnemies[i]->Update();
	}
}

void EnemyManager::Render() {
	for (unsigned int i = 0; i < _lesserEnemies.size(); i++) {
		_lesserEnemies[i]->Render();
	}
}

void EnemyManager::CreateEnemy(EnemyType enemyType, LesserEnemy* lesserEnemy) {
	switch (enemyType) {
	case EnemyType::LesserEnemy:
		_lesserEnemies.emplace_back(lesserEnemy);
		lesserEnemy->Init();
		break;

	default:
		break;
	}
	
}
