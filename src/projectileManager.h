#pragma once
#include "projectile.h"

#include <vector>


class ProjectileManager {
public:
	ProjectileManager();
	~ProjectileManager();

	void Init();
	void Update();
	void Render();

	bool CheckCollision(DamageType damageType, unsigned int projectileIndex);

	void AddNewProjectile(DamageType damageType, float orientation,
		Vector2<float> direction, Vector2<float> position);
	void SpawnProjectile(DamageType damageType, float orientation,
		Vector2<float> direction, Vector2<float> position);
	void RemoveAllProjectiles();
	void RemoveProjectile(DamageType damageType, unsigned int projectileIndex);

	std::vector<Projectile*> GetActiveProjectiles();

private:
	std::vector<Projectile*> _activeEnemyProjectiles;
	std::vector<Projectile*> _inactiveEnemyProjectiles;

	std::vector<Projectile*> _activePlayerProjectiles;
	std::vector<Projectile*> _inactivePlayerProjectiles;

	Circle _intersectedCollider;
	Circle _currentCollider;

	unsigned int _latestProjectileID = 0;

};

