#include "enemyManager.h"

#include "enemyBase.h"
#include "enemyFighter.h"
#include "enemyWizard.h"

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

void EnemyManager::CreateEnemy(EnemyType enemyType, Vector2<float> position) {
	switch (enemyType) {
	case EnemyType::EnemyFighter:
		_allEnemies.emplace_back(new EnemyFighter("res/sprites/CoralineDadFighter.png", 30, position));
		break;

	case EnemyType::EnemyWizard:
		_allEnemies.emplace_back(new EnemyWizard("res/sprites/CoralineDadWizard.png", 20, position));
		break;
	default:
		break;
	}
	_allEnemies.back()->Init();
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

std::vector<EnemyBase*> EnemyManager::GetAllEnemies() {
	return _allEnemies;
}
