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
	const float GetOrientation() const override;
	const int GetCurrentHealth() const override;
	const Sprite* GetSprite() const override;
	const Vector2<float> GetPosition() const override;

	void ActivateEnemy(float orienation, Vector2<float> direction, Vector2<float> position);
	void DeactivateEnemy() override;

private:
	void UpdateAttack();
	void UpdateMovement();
	void UpdateTarget();

	const float _attackRange = 200.f;
	const float _movementSpeed = 50.f;
	const unsigned int _attackDamage = 0;

	Sprite* _sprite = nullptr;
	Vector2<float> _position = Vector2<float>(-10000.f, -10000.f);
	Vector2<float> _targetPosition = Vector2<float>(0.f, 0.f);
	Vector2<float> _direction = Vector2<float>(0.f, 0.f);


};

