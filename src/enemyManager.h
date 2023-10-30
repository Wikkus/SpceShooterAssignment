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

	std::vector<EnemyBase*> GetActiveEnemies();

	void CreateEnemy(EnemyType enemyType, float orientation,
		Vector2<float> direction, Vector2<float> position);

	void DeactivateAllEnemies();
	void DeactivateEnemy(unsigned int enemyID);

	void TakeDamage(unsigned int enemyIndex, unsigned int damageAmount);

private:
	std::vector<EnemyBase*> _activeEnemies;
	std::vector<EnemyBase*> _inactiveEnemies;

};

