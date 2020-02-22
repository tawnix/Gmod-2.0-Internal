#pragma once
#include <cmath>
#include "Interface.h"

class Math
{
public:
	float GetDistanceBetween(Vector LocalPlayerCoordinates, Vector EnemyPlayerCoordinates);

	Vector CalcAngle(Vector LocalPlayerOrigin, Vector EnemyPlayerOrigin);

	float GetDistAngles(Vector myViewAngles, Vector desViewAngles);

	bool WorldToScreen(Vector& in, Vector& out);

    RECT GetViewport();


};