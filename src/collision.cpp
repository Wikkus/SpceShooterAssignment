#include "collision.h"
#include "debugDrawer.h"
#include "gameEngine.h"

#include <minmax.h>
#include <SDL2/SDL.h>

#define PI 3.1415

AABB AABB::makeFromPositionSize(float x, float y, float w, float h) {
	AABB boxCollider;
	boxCollider.xMin = x - w / 2;
	boxCollider.yMin = y - h / 2;
	boxCollider.xMax = x + w / 2;
	boxCollider.yMax = y + h / 2;
	boxCollider.detectionOffset;
	return boxCollider;
}

bool CircleIntersect(Circle& circleA, Circle& circleB) {
	float dx = circleB.X - circleA.X;
	float dy = circleB.Y - circleA.Y;

	float distanceSquared = dx * dx + dy * dy;
	float distance = sqrt(distanceSquared);

	float radiusSum = circleA.radius + circleB.radius;
	return distance < radiusSum;
}

bool AABBIntersect(AABB& boxA, AABB& boxB) {
	return (
		boxA.xMax > boxB.xMin && 
		boxB.xMax > boxA.xMin &&
		boxA.yMax > boxB.yMin &&
		boxB.yMax > boxA.yMin);
}


float Clamp(float a, float min, float max) {
	if (a < min) {
		return min;
	}
	else if (a > max) {
		return max;
	}
	return a;
}

bool AABBCircleIntersect(AABB& box, Circle& circle) {
	float clampedX = Clamp(circle.X, box.xMin, box.xMax);
	float clampedY = Clamp(circle.Y, box.yMin, box.yMax);

	float deltaX = circle.X - clampedX;
	float deltaY = circle.Y - clampedY;

	float distanceSquared = deltaX * deltaX + deltaY * deltaY;
	float distance = sqrt(distanceSquared);
	return (distance < circle.radius);
}