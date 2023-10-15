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

private:
	std::vector<LesserEnemy*> _lesserEnemies;

};

