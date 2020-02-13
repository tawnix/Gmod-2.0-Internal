#pragma once
#include "SDK Stuff.h"
#include <Windows.h>

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

class CCreateInterface
{
private:
	CreateInterfaceFn GetModuleFactory(HMODULE module)
	{
		return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface"));
	}

	template<typename T>
	T GetInterface(CreateInterfaceFn fn, const char* szInterfaceVersion)
	{
		auto result = reinterpret_cast<T>(fn(szInterfaceVersion, nullptr));
		if (!result) return nullptr;
		return result;
	}
public:
	static CCreateInterface& GetInstance()
	{
		CCreateInterface CreateInterface;
		return CreateInterface;
	}
	void Initialize();
};

struct CInterfaces
{
	static IClientEntityList* pEntityList;
	static IEngineClient* pEngine;
	static IVModelInfo* pModelInfo;
	static CHLClient* pClient;
};
