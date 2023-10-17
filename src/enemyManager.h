#pragma once
#include "vector2.h"

#include <vector>

enum class EnemyType {
	EnemyFighter, 
	EnemyWizard,
	Count
};

class EnemyBase;
class EnemyFighter;

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Update();
	void Render();

	void CreateEnemy(EnemyType enemyType, Vector2<float> position);

	void RemoveAllEnemies();
	void RemoveEnemy(unsigned int enemyIndex);

	void TakeDamage(unsigned int enemyIndex, unsigned int damageAmount);

	std::vector<EnemyBase*> GetAllEnemies();

private:
	std::vector<EnemyBase*> _allEnemies;
};

