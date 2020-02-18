#pragma once
#include "Interface.h"
#include "Math.h"
#include "Aimbot.h"



class ESP {
public:
	Math oMath;
	aimbot oAim;
	
	//loop through entities and draw them.
	void DrawBox();
	void DrawText2();
	void DrawName();

	bool IsValid(IClientEntity* ent);



	bool bESP = false;
	bool bMenu = true;
	bool bAimbot = false;



	Color Menu = { 255, 255, 255, 255 };
	Color Activated = { 0, 255, 0, 255 };
	Color NonActivated = { 255, 255, 255, 255 };
	Color Red = { 255, 0, 0, 255 };
	Color Blue = { 0, 0, 255, 255 };


};


