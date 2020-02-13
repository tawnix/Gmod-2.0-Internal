#include "Interface.h"


IClientEntityList* CInterfaces::pEntityList;
IEngineClient* CInterfaces::pEngine;
IVModelInfo* CInterfaces::pModelInfo;
CHLClient* CInterfaces::pClient;

void CCreateInterface::Initialize()
{
	auto clientFactory = GetModuleFactory(GetModuleHandle("client.dll"));
	auto engineFactory = GetModuleFactory(GetModuleHandle("engine.dll"));

	CInterfaces::pEntityList = GetInterface<IClientEntityList*>(clientFactory, "VClientEntityList003");
	CInterfaces::pEngine = GetInterface<IEngineClient*>(engineFactory, "VEngineClient015");
	CInterfaces::pModelInfo = GetInterface<IVModelInfo*>(engineFactory, "VModelInfoClient006");
	CInterfaces::pClient = GetInterface<CHLClient*>(clientFactory, "VClient017");

}
