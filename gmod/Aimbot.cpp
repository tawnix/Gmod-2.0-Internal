#include "Aimbot.h"


IClientEntity* aimbot::GetBestEnt()
{
	float oldDifference = 99999999.0f; 
	float currDiff = 0.0f;
	short int bestEnt = 0;

	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pCurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (!IsValid(pCurrentEnt))
			continue;

		currDiff = oMath.GetDistanceBetween(pLocalPlayer->GetOrigin(), pCurrentEnt->GetOrigin());

		if (currDiff < oldDifference)
		{
			bestEnt = i;
			oldDifference = currDiff;
		}
	}
	return (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(bestEnt);
}

bool aimbot::IsValid(IClientEntity* ent)
{
	if (ent == nullptr)
		return false;

	if (ent == pLocalPlayer)
		return false;

	if (ent->GetClientClass()->m_ClassID != 70)
		return false;

	if (ent->GetHealth() <= 0 || ent->GetHealth() >= 999999)
		return false;

	return true;
}

int aimbot::GetHeadBone(IClientEntity* ent, const char* boneName)
{
	int aimbone;
	matrix3x4_t pMatrix[128];

	ent->SetupBones(pMatrix, 128, 0x00000100, 0.0f);

	auto pStudioModel = CInterfaces::pModelInfo->GetStudioModel(ent->GetModel());

	if (!pStudioModel)
		return false;

	auto set = pStudioModel->pHitboxSet(0);

	if (!set)
		return false;

	for (int c = 0; c < set->numhitboxes; c++)
	{
		auto pHitBox = set->pHitbox(c);

		if (!pHitBox)
			return false;

		auto cHitBoxName = pStudioModel->pBone(pHitBox->bone)->pszName();

		// use strstr because its fastest algorithim for comparing strings !!!!!!! niggers
		if (boneName && strstr(cHitBoxName, boneName))
		{
			aimbone = pHitBox->bone;
		}
	}

	return aimbone;
}

Vector aimbot::GetBonePos(IClientEntity* ent, int boneIndex)
{
	matrix3x4_t bonePos[128];
	Vector vHeadPos;
	ent->SetupBones(bonePos, 128, 0x00000100, 0.0f);

	matrix3x4_t Hitbox = bonePos[boneIndex];

	vHeadPos.x = Hitbox[0][3];
	vHeadPos.y = Hitbox[1][3];
	vHeadPos.z = Hitbox[2][3];

	return vHeadPos;
}

void aimbot::StartAim()
{
	IClientEntity* pCurrentEnt = (IClientEntity*)GetBestEnt();

	int headBoneIndex = GetHeadBone(pCurrentEnt, boneArray[12]);
	Vector bonePosition = GetBonePos(pCurrentEnt, headBoneIndex);

	toAim = oMath.CalcAngle(pLocalPlayer->GetOrigin(), bonePosition);

}

