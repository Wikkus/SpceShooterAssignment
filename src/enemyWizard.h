#pragma once
#include "collision.h"
#include "enemyBase.h"
#include "sprite.h"
#include "vector2.h"

class EnemyWizard : public EnemyBase {
public:
	EnemyWizard();
	~EnemyWizard();

	void Init() override;
	void Update() override;
	void Render() override;

	bool TakeDamage(unsigned int damageAmount) override;

	const Circle GetCollider() const override;
	const EnemyType GetEnemyType() const override;
	const float GetAttackDamage() const override;
	const float GetAttackRange() const override;
	const float GetOrientation() const override;
	const int GetCurrentHealth() const override;
	const unsigned int GetID() const override;
	const Sprite* GetSprite() const override;
	const Timer* GetAttackTimer() const override;
	const Vector2<float> GetPosition() const override;
	const std::vector<EnemyBase*> GetQueriedEnemies() const override;

	void ActivateEnemy(float orienation, unsigned int id, Vector2<float> direction, Vector2<float> position) override;
	void DeactivateEnemy() override;
	void ExecuteAttack() override;

private:
	void UpdateMovement();
	void UpdateTarget();

	const float _attackRange = 200.f;
	const float _movementSpeed = 50.f;
	const unsigned int _attackDamage = 10;


};

