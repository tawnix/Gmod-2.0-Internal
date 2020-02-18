#include "Aimbot.h"


void aimbot::StartAim()
{
	IClientEntity* pCurrentEnt = (IClientEntity*)EntStuff.GrabClosestEnt();

	int headBoneIndex = EntStuff.GrabBone(pCurrentEnt, boneArray[12]);
	Vector bonePosition = EntStuff.GetBonePos(pCurrentEnt, headBoneIndex);

	toAim = EntStuff.oMath.CalcAngle(EntStuff.pLocalPlayer->GetOrigin(), bonePosition);

}

