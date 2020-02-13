#include "Math.h"

float Math::GetDistanceBetween(Vector LocalPlayerCoordinates, Vector EnemyPlayerCoordinates)
{
	double Distance = 0.0f;

	Distance =
		sqrt(pow(EnemyPlayerCoordinates.x - LocalPlayerCoordinates.x, 2) + pow(EnemyPlayerCoordinates.y - LocalPlayerCoordinates.y, 2) + pow(EnemyPlayerCoordinates.z - LocalPlayerCoordinates.z, 2)
		);

	return (float)Distance;
}

Vector Math::CalcAngle(Vector LocalPlayerOrigin, Vector EnemyPlayerOrigin)
{
	LocalPlayerOrigin.z += 64.0f;
	Vector Difference;
	Difference = EnemyPlayerOrigin - LocalPlayerOrigin;


	float magnitude = sqrt(pow(Difference.x, 2) + pow(Difference.y, 2) + pow(Difference.z, 2));

	Vector AngleToAim;

	AngleToAim.y = atan2f(Difference.y, Difference.x) * 180 / 3.14;

	AngleToAim.x = -asinf(Difference.z / magnitude) * 180 / 3.14;


	if (AngleToAim.x > 89)
		AngleToAim.x = 89;

	if (AngleToAim.x < -89)
		AngleToAim.x = -89;

	while (AngleToAim.y > 180) { AngleToAim.y -= 360; }

	while (AngleToAim.y < -180) { AngleToAim.y += 360; }


	AngleToAim.z = 0.0f;



	return AngleToAim;
}

float Math::GetDistAngles(float* AngleYaw, float* AnglePitch, Vector AnglesToAim)
{
	double dist = 0.000;

	dist = sqrt(pow(AnglesToAim.y - *AngleYaw, 2) + pow(AnglesToAim.x - *AnglePitch, 2));


	return (float)dist;
}