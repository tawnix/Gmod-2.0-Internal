#include "ESP.h"

void ESP::DrawBox()
{
	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* CurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (IsValid(CurrentEnt) == false)
			continue;

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
}

void ESP::DrawText2()
{
	if (GetAsyncKeyState(VK_NUMPAD0) && 1)
		bESP = !bESP;

	if (GetAsyncKeyState(VK_NUMPAD5) && 1)
		bMenu = !bMenu;

	
	if (bMenu)
	{
		CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 600, 0, 0, 0);
		CInterfaces::pSurface->DrawSetTextColor2(Menu);
		CInterfaces::pSurface->DrawSetTextPos2(0, 0);
		CInterfaces::pSurface->DrawPrintText2(L"Gmod Internal 2.0", wcslen(L"Gmod Internal 2.0"));

		if (bESP)
		{
			CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 500, 0, 0, 0);
			CInterfaces::pSurface->DrawSetTextColor2(Activated);
			CInterfaces::pSurface->DrawSetTextPos2(0, 30);
			CInterfaces::pSurface->DrawPrintText2(L"ESP", wcslen(L"ESP"));
			DrawBox();
		}
		else
		{
			CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 500, 0, 0, 0);
			CInterfaces::pSurface->DrawSetTextColor2(NonActivated);
			CInterfaces::pSurface->DrawSetTextPos2(0, 30);
			CInterfaces::pSurface->DrawPrintText2(L"ESP", wcslen(L"ESP"));
		}


		if (bAimbot)
		{
			CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 500, 0, 0, 0);
			CInterfaces::pSurface->DrawSetTextColor2(Activated);
			CInterfaces::pSurface->DrawSetTextPos2(0, 60);
			CInterfaces::pSurface->DrawPrintText2(L"Aimbot", wcslen(L"Aimbot"));
		}
		else
		{
			CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 500, 0, 0, 0);
			CInterfaces::pSurface->DrawSetTextColor2(NonActivated);
			CInterfaces::pSurface->DrawSetTextPos2(0, 60);
			CInterfaces::pSurface->DrawPrintText2(L"Aimbot", wcslen(L"Aimbot"));
		}



	}

	//Color poo = { 255, 255, 255, 255 };
	//const wchar_t* poopy = L"Hello";
	//CInterfaces::pSurface->DrawSetTextColor2(poo);
	//CInterfaces::pSurface->DrawSetTextFont2(2);
	//CInterfaces::pSurface->DrawSetTextPos2(100, 100);
	//CInterfaces::pSurface->DrawPrintText2(poopy, std::char_traits<wchar_t>::length(poopy));
}

void ESP::DrawName()
{
	CInterfaces::pSurface->SetGlpyhSet2(2, "Tahoma", 10, 500, 0, 0, 0);
	CInterfaces::pSurface->DrawSetTextColor2(Red);
	Vector out;

	player_info_t pinfo;

	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* CurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (IsValid(CurrentEnt) == false)
			continue;

		Vector WorldToScreenEnt, CurrentOrg;

		CurrentOrg = CurrentEnt->GetOrigin();

		if (EntStuff.oMath.WorldToScreen(CurrentOrg, WorldToScreenEnt))
		{
			CInterfaces::pSurface->DrawSetTextColor2(Blue);
			CInterfaces::pSurface->DrawSetTextPos2(WorldToScreenEnt.x, WorldToScreenEnt.y);
			CInterfaces::pEngine->GetPlayerInfo(i, &pinfo);
			size_t origsize = strlen(pinfo.Name) + 1;
			const size_t newsize = 100;
			size_t convertedChars = 0;
			wchar_t wcstring[newsize];
			mbstowcs_s(&convertedChars, wcstring, origsize, pinfo.Name, _TRUNCATE);
			CInterfaces::pSurface->DrawPrintText2(wcstring, wcslen(wcstring));
		}
	}

	//CInterfaces::pSurface->DrawSetTextPos2(0, 60);
	//CInterfaces::pSurface->DrawPrintText2(L"Aimbot", std::char_traits<wchar_t>::length(L"Aimbot"));
	
}


bool ESP::IsValid(IClientEntity* ent)
{
	if (ent == NULL)
		return false;
	if (ent == EntStuff.pLocalPlayer)
		return false;
	if (ent->GetClientClass()->m_ClassID != 70)
		return false;
	if (ent->GetHealth() <= 0 || ent->GetHealth() >= 999999999)
		return false;
	return true;
}

