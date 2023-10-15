#pragma once
#include "vector2.h"

bool OutOfBorderX(float positionX);
bool OutOfBorderY(float positionY);

Vector2<float> GetMousePosition();

Vector2<float>  OrientationAsVector(float orientation);

float VectorAsOrientation(Vector2<float> direction);

float WrapMax(float rotation, float maxValue);
float WrapMinMax(float rotation, float minValue, float maxValue);