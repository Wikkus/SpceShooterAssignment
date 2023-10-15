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



private:
	std::vector<Projectile*> _activeProjectiles;

};

