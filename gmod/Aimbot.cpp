#include "Aimbot.h"


IClientEntity* aimbot::GetClosestToXHair(CUserCmd* cmd)
{
	float oldDifference = 9999999.0f;
	short int bestEnt = 0;

	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pCurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (EntStuff.IsValid(pCurrentEnt) == false)
			continue;

		int headBoneIndex = EntStuff.GrabBone(pCurrentEnt, boneArray[12]);
		Vector bonePosition = EntStuff.GetBonePos(pCurrentEnt, headBoneIndex);


		if (EntStuff.GetVisible(EntStuff.pLocalPlayer->GetOrigin(), bonePosition, pCurrentEnt) == false)
			continue;

		Vector dest = EntStuff.oMath.CalcAngle(EntStuff.pLocalPlayer->GetOrigin(), bonePosition);

		Vector myViewAngles;
		myViewAngles.x = cmd->m_viewangles.x;
		myViewAngles.y = cmd->m_viewangles.y;

		// get distance between my yaw and yaw to aim at the enemy
		float fYawDifference = EntStuff.oMath.GetDistAngles(myViewAngles, dest);

		if (fYawDifference > 50.0f)
			continue;


		if (fYawDifference < oldDifference)
		{
			oldDifference = fYawDifference;
			bestEnt = i;
		}
		
	}
	return (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(bestEnt);
}

void aimbot::StartAim(CUserCmd* cmd)
{
	IClientEntity* pCurrentEnt = GetClosestToXHair(cmd);

	if (pCurrentEnt == EntStuff.pLocalPlayer)
		return;

	int headBoneIndex = EntStuff.GrabBone(pCurrentEnt, boneArray[12]);
	Vector bonePosition = EntStuff.GetBonePos(pCurrentEnt, headBoneIndex);

	toAim = EntStuff.oMath.CalcAngle(EntStuff.pLocalPlayer->GetOrigin(), bonePosition);

	float difference = EntStuff.oMath.GetDistAngles(cmd->m_viewangles, toAim);

	

	if (difference < 20 && difference > -20)
	{
		float newX = cmd->m_viewangles.x;
		float newY = cmd->m_viewangles.y;

		Vector Diffs;
		Diffs.x = toAim.x - newX;
		Diffs.y = toAim.y - newY;


		newX += Diffs.x / 20.0f;

		if (newX > 180)
			newX -= 360;
		if (newX < -180)
			newX += 360;

		newY += Diffs.y / 20.0f;



		if (toAim.x - newX  < 2.0f && toAim.x - newX > -2.0f)
			newX = toAim.x;
		if (toAim.y - newY < 2.0f && toAim.y - newY > -2.0f)
			newY = toAim.y;

		toAim.x = newX;
		toAim.y = newY;
	}
	else
	{
		toAim = cmd->m_viewangles;

	}
}

