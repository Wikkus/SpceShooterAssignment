#include "enemyManager.h"

#include "lesserEnemy.h"

EnemyManager::EnemyManager() {}

EnemyManager::~EnemyManager() {
	for (unsigned int i = 0; i < _allEnemies.size(); i++) {
		RemoveEnemy(i);;
	}
}

void EnemyManager::Init() {
	for (unsigned int i = 0; i < _allEnemies.size(); i++) {
		_allEnemies[i]->Init();
	}
}

void EnemyManager::Update() {
	for (unsigned int i = 0; i < _allEnemies.size(); i++) {
		_allEnemies[i]->Update();
	}
}

void EnemyManager::Render() {
	for (unsigned int i = 0; i < _allEnemies.size(); i++) {
		_allEnemies[i]->Render();
	}
}

void EnemyManager::CreateEnemy(EnemyType enemyType, LesserEnemy* lesserEnemy) {
	switch (enemyType) {
	case EnemyType::LesserEnemy:
		_allEnemies.emplace_back(lesserEnemy);
		lesserEnemy->Init();
		break;

	default:
		break;
	}
	
}

void EnemyManager::RemoveAllEnemies() {
	while (_allEnemies.size() > 0) {
		RemoveEnemy(_allEnemies.size() - 1);
	}
}

void EnemyManager::RemoveEnemy(unsigned int enemyIndex) {
	_allEnemies[enemyIndex] = nullptr;
	delete _allEnemies[enemyIndex];
	std::swap(_allEnemies[enemyIndex], _allEnemies.back());
	_allEnemies.pop_back();
}

void EnemyManager::TakeDamage(unsigned int enemyIndex, unsigned int damageAmount) {
	//TakeDamage returns true if the enemy dies
	if(_allEnemies[enemyIndex]->TakeDamage(damageAmount)) {
		RemoveEnemy(enemyIndex);
	}
}

std::vector<LesserEnemy*> EnemyManager::GetEnemies() {
	return _allEnemies;
}
