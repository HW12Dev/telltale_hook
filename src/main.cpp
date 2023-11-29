#include <Windows.h>

#include <filesystem>
#include <string>
#include <tchar.h>
#include <iostream>

#include "telltale_hook.hpp"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved) {

    static wchar_t s_PathBuffer[8192];

    if (fdwReason == DLL_PROCESS_ATTACH) {

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)telltale_hook::setup, NULL, NULL, NULL);
		//telltale_hook::setup();
    }
	if (fdwReason == DLL_PROCESS_DETACH) {
	}
	return TRUE;
}