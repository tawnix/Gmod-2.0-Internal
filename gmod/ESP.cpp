#include "ESP.h"

void ESP::DrawBox(IClientEntity* CurrentEnt)
{
	CInterfaces::pSurface->DrawSetColor2(255, 0, 0, 255);

	Vector footPosOut, headPos;

	int headBone = EntStuff.GrabBone(CurrentEnt, EntStuff.boneArray[12]);
	Vector bonePos = EntStuff.GetBonePos(CurrentEnt, headBone);
	int footBone = EntStuff.GrabBone(CurrentEnt, EntStuff.boneArray[7]);
	Vector footPos = EntStuff.GetBonePos(CurrentEnt, footBone);

	if (EntStuff.oMath.WorldToScreen(bonePos, headPos) && EntStuff.oMath.WorldToScreen(footPos, footPosOut))
	{
		CInterfaces::pSurface->DrawOutlineRect2(headPos.x, headPos.y, footPosOut.x, footPosOut.y);
	}
}

void ESP::DrawText2(IClientEntity* CurrentEnt)
{
	if (bMenu)
	{
		CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 600, 0, 0, 0);
		CInterfaces::pSurface->DrawSetTextColor2(Menu);
		CInterfaces::pSurface->DrawSetTextPos2(0, 0);
		CInterfaces::pSurface->DrawPrintText2(L"Gmod Internal 2.1", wcslen(L"Gmod Internal 2.1"));
	}
}

void ESP::DrawName(IClientEntity* CurrentEnt, int entIndex)
{
	CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 300, 0, 0, 0);
	
	Vector out;

	player_info_t pinfo;

	Vector WorldToScreenEnt, CurrentOrg;

	CurrentOrg = CurrentEnt->GetOrigin();

	if (EntStuff.oMath.WorldToScreen(CurrentOrg, WorldToScreenEnt))
	{
		float distance = EntStuff.oMath.GetDistanceBetween(EntStuff.pLocalPlayer->GetOrigin(), CurrentEnt->GetOrigin());

		int dist = (int)distance;

		std::string output = std::to_string(distance);

		CInterfaces::pSurface->DrawSetTextColor2(Menu);
		CInterfaces::pSurface->DrawSetTextPos2(WorldToScreenEnt.x, WorldToScreenEnt.y);
		CInterfaces::pEngine->GetPlayerInfo(entIndex, &pinfo);
		size_t origsize = strlen(pinfo.Name) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, pinfo.Name, _TRUNCATE);


		CInterfaces::pSurface->DrawPrintText2(wcstring, wcslen(wcstring));
		// DRAW DISTANCE
		CInterfaces::pSurface->DrawSetTextPos2(WorldToScreenEnt.x, WorldToScreenEnt.y + 10 );
		CInterfaces::pSurface->DrawPrintText2(std::to_wstring(dist).c_str(), wcslen(std::to_wstring(dist).c_str()));
	}
}

void ESP::DrawSnapline(IClientEntity* CurrentEnt)
{
	CInterfaces::pSurface->DrawSetColor2(255, 0, 0, 255);

	Vector WorldToScreenEnt, CurrentOrg;

	CurrentOrg = CurrentEnt->GetOrigin();

	if (EntStuff.oMath.WorldToScreen(CurrentOrg, WorldToScreenEnt))
	{
		int w, h;
		CInterfaces::pEngine->GetScreenSize(w, h);
		CInterfaces::pSurface->DrawSetTextColor2(Red);
		CInterfaces::pSurface->DrawLine2(WorldToScreenEnt.x, WorldToScreenEnt.y, w / 2, h);
	}
}

void ESP::DrawHealthValue(IClientEntity* CurrentEnt)
{
	CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 8, 200, 0, 0, 0);

	Vector WorldToScreenEnt, CurrentOrg;

	CurrentOrg = CurrentEnt->GetOrigin();
	int EntHealth = CurrentEnt->GetHealth();

	if (EntStuff.oMath.WorldToScreen(CurrentOrg, WorldToScreenEnt))
	{
		if (EntHealth >= 70)
			CInterfaces::pSurface->DrawSetTextColor2(Activated);

		if (EntHealth <= 69)
			CInterfaces::pSurface->DrawSetTextColor2(Yellow);

		if (EntHealth <= 40)
			CInterfaces::pSurface->DrawSetTextColor2(Red);


		CInterfaces::pSurface->DrawSetTextPos2(WorldToScreenEnt.x, WorldToScreenEnt.y + 20);

		CInterfaces::pSurface->DrawPrintText2(std::to_wstring(EntHealth).c_str(), wcslen(std::to_wstring(EntHealth).c_str()));
	}
}

bool ESP::DrawESP()
{
	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* CurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (EntStuff.IsValid(CurrentEnt) == false)
			 continue;

		DrawBox(CurrentEnt);
		DrawName(CurrentEnt, i);
		DrawSnapline(CurrentEnt);
		DrawHealthValue(CurrentEnt);
	}

	return true;
}

