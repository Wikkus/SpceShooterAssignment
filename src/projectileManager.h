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

	void CreateProjectile(Projectile* projectile);

	bool CheckCollision(unsigned int projectileIndex);

	void RemoveAllProjectiles();

	void RemoveProjectile(unsigned int projectileIndex);


private:
	std::vector<Projectile*> _activeProjectiles;
	Circle _intersectedCollider;
	Circle _currentCollider;

};

