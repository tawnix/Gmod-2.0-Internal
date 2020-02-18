#include "Hooks.h"



int main()
{
	FILE* pFile = nullptr;
	AllocConsole();
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	CCreateInterface::GetInstance().Initialize();

	InitaliseHooks();

	while (true)
	{
		if (GetAsyncKeyState(VK_F6))
			break;

	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
