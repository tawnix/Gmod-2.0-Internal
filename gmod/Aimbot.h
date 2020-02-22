#pragma once
#include <iostream>
#include "Entity.h"


#define PI 3.1415926535897


class aimbot
{
public:
	float currDiff = 0.0f;
	EntityStuff EntStuff;
	Vector toAim;

	IClientEntity* GetClosestToXHair(CUserCmd* cmd);
	void StartAim(CUserCmd* cmd);


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