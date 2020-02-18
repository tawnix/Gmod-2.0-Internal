#pragma once
#include "SDK Stuff.h"
#include "Interface.h"
#include "Math.h"

class EntityStuff
{
public:
	Math oMath;

	IClientEntity* pLocalPlayer;
	EntityStuff()
	{
		pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
	}

	IClientEntity* GrabClosestEnt();
	bool IsValid(IClientEntity* ent);
	int GrabBone(IClientEntity* ent, const char* boneName);
	Vector GetBonePos(IClientEntity* ent, int boneIndex);


	const char* boneArray[19] = {
		"ValveBiped.Bip01_Pelvis",
		"ValveBiped.Bip01_L_Thigh",
		"ValveBiped.Bip01_L_Calf",
		"ValveBiped.Bip01_L_Foot",
		"ValveBiped.Bip01_L_Toe0",
		"ValveBiped.Bip01_R_Thigh",
		"ValveBiped.Bip01_R_Calf",
		"ValveBiped.Bip01_R_Foot",
		"ValveBiped.Bip01_R_Toe0",
		"ValveBiped.Bip01_Spine1",
		"ValveBiped.Bip01_Spine2",
		"ValveBiped.Bip01_Neck1",
		"ValveBiped.Bip01_Head1",
		"ValveBiped.Bip01_L_UpperArm",
		"ValveBiped.Bip01_L_Forearm",
		"ValveBiped.Bip01_L_Hand",
		"ValveBiped.Bip01_R_UpperArm",
		"ValveBiped.Bip01_R_Forearm" };

};
