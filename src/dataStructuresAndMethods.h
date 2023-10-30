#pragma once
#include "vector2.h"

bool IsInDistance(Vector2<float> positionA, Vector2<float> positionB, float distance);
bool OutOfBorderX(float positionX);
bool OutOfBorderY(float positionY);

Vector2<float> GetCursorPosition();

Vector2<float>  OrientationAsVector(float orientation);

float VectorAsOrientation(Vector2<float> direction);

float WrapMax(float rotation, float maxValue);
float WrapMinMax(float rotation, float minValue, float maxValue);