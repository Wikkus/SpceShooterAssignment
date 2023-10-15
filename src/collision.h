#pragma once
#include "vector2.h"

struct Circle {
	Vector2<float> position;
	float radius;
};

struct Collision {
	Vector2<float> position = Vector2<float>(0, 0);
	Vector2<float> normal = Vector2<float>(0,0);

	bool collisionDetected = false;
};

struct AABB {
	static AABB makeFromPositionSize(float x, float y, float w, float h);

	Vector2<float> topLeft = Vector2<float>(0, 0);
	Vector2<float> topRight = Vector2<float>(0, 0);
	Vector2<float> bottomLeft = Vector2<float>(0, 0);
	Vector2<float> bottomRight = Vector2<float>(0, 0);

	float detectionOffset = 1.f;

	float xMin = 0.f;
	float xMax = 0.f;

	float yMin = 0.f;
	float yMax = 0.f;
};

bool CircleIntersect(Circle& circleA, Circle& circleB);

bool AABBIntersect(AABB& boxA, AABB& boxB);

bool AABBCircleIntersect(AABB& box, Circle& circle);