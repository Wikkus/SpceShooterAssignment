#pragma once


#include <vector>

enum class EnemyType {
	LesserEnemy, 
	Count
};


class LesserEnemy;

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Update();
	void Render();

	void CreateEnemy(EnemyType enemyType, LesserEnemy* lesserEnemy);

	void RemoveAllEnemies();
	void RemoveEnemy(unsigned int enemyIndex);

	void TakeDamage(unsigned int enemyIndex, unsigned int damageAmount);

	std::vector<LesserEnemy*> GetEnemies();

private:
	std::vector<LesserEnemy*> _allEnemies;

};

