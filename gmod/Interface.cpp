#include "Interface.h"


IClientEntityList* CInterfaces::pEntityList;
IEngineClient* CInterfaces::pEngine;
IVModelInfo* CInterfaces::pModelInfo;
CHLClient* CInterfaces::pClient;
IPanel* CInterfaces::pPanel;
ISurface* CInterfaces::pSurface;

void CCreateInterface::Initialize()
{
	auto clientFactory = GetModuleFactory(GetModuleHandle("client.dll"));
	auto engineFactory = GetModuleFactory(GetModuleHandle("engine.dll"));
	auto vGUIFactory = GetModuleFactory(GetModuleHandle("vgui2.dll"));
	auto vGUIMatsurface = GetModuleFactory(GetModuleHandle("vguimatsurface.dll"));

	CInterfaces::pEntityList = GetInterface<IClientEntityList*>(clientFactory, "VClientEntityList003");
	CInterfaces::pEngine = GetInterface<IEngineClient*>(engineFactory, "VEngineClient015");
	CInterfaces::pModelInfo = GetInterface<IVModelInfo*>(engineFactory, "VModelInfoClient006");
	CInterfaces::pClient = GetInterface<CHLClient*>(clientFactory, "VClient017");
	CInterfaces::pPanel = GetInterface<IPanel*>(vGUIFactory, "VGUI_Panel009");
	CInterfaces::pSurface = GetInterface<ISurface*>(vGUIMatsurface, "VGUI_Surface030");
}
