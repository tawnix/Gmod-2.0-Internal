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

}

