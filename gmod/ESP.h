#pragma once
#include "Interface.h"
#include "Entity.h"
#include <string>
using namespace std;




class ESP {
public:
	EntityStuff EntStuff;
	//loop through entities and draw them.
	void DrawBox();
	void DrawText2();
	void DrawName();
	void DrawHealthValue();
	void DrawBoundBox(IClientEntity* ent, Color clr);




	bool bESP = true;
	bool bMenu = true;
	bool bAimbot = false;



	Color Menu = { 255, 255, 255, 255 };
	Color Activated = { 0, 255, 0, 255 };
	Color NonActivated = { 255, 255, 255, 255 };
	Color Red = { 255, 0, 0, 255 };
	Color Blue = { 0, 0, 255, 255 };
	Color Green = { 0, 255, 0, 255 };
	Color Yellow = { 255, 255, 0, 255 };
	Color RandomCol = { 150, 0, 130, 255 };


};


