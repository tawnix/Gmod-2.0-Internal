#include "Math.h"

float Math::GetDistanceBetween(Vector LocalPlayerCoordinates, Vector EnemyPlayerCoordinates)
{
	double Distance = 0.0f;

	Distance = sqrt(pow(EnemyPlayerCoordinates.x - LocalPlayerCoordinates.x, 2) + pow(EnemyPlayerCoordinates.y - LocalPlayerCoordinates.y, 2) + pow(EnemyPlayerCoordinates.z - LocalPlayerCoordinates.z, 2));

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

float Math::GetDistAngles(Vector myViewAngles, Vector desViewAngles)
{
	float dist;

	dist = sqrt(pow(myViewAngles.x - desViewAngles.x, 2) + pow(myViewAngles.y - desViewAngles.y, 2));

	return dist;


}



bool Math::WorldToScreen(Vector& in, Vector& out)
{
	const matrix3x4_t& worldToScreen = CInterfaces::pEngine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	out.z = 0; //Screen doesn't have a 3rd dimension.

	if (w > 0.001) //If the object is within view.
	{
		RECT ScreenSize = GetViewport();
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f); //Get the X dimension and push it in to the Vector.
		out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

RECT Math::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	CInterfaces::pEngine->GetScreenSize(w, h);
	Viewport.right = w;
	Viewport.bottom = h;
	return Viewport;
}
