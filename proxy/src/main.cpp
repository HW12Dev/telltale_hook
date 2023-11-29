#include <Windows.h>
#include <filesystem>

static HMODULE telltale_hook = nullptr;

struct dinput8_dll
{
    HMODULE dll;
    FARPROC OrignalDirectInput8Create;
    FARPROC OrignalDllCanUnloadNow;
    FARPROC OrignalDllGetClassObject;
    FARPROC OrignalDllRegisterServer;
    FARPROC OrignalDllUnregisterServer;
    FARPROC OrignalGetdfDIJoystick;
} dinput8;

__declspec(naked) void FakeDirectInput8Create()
{
    _asm { jmp[dinput8.OrignalDirectInput8Create] }
}
__declspec(naked) void FakeDllCanUnloadNow()
{
    _asm { jmp[dinput8.OrignalDllCanUnloadNow] }
}
__declspec(naked) void FakeDllGetClassObject()
{
    _asm { jmp[dinput8.OrignalDllGetClassObject] }
}
__declspec(naked) void FakeDllRegisterServer()
{
    _asm { jmp[dinput8.OrignalDllRegisterServer] }
}
__declspec(naked) void FakeDllUnregisterServer()
{
    _asm { jmp[dinput8.OrignalDllUnregisterServer] }
}
__declspec(naked) void FakeGetdfDIJoystick()
{
    _asm { jmp[dinput8.OrignalGetdfDIJoystick] }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    char path[MAX_PATH];
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 13), "\\dinput8.dll", 14);
        dinput8.dll = LoadLibrary(path);
        if (dinput8.dll == NULL)
        {
            MessageBox(0, "Cannot load original dinput8.dll library", "Proxy", MB_ICONERROR);
            ExitProcess(0);
        }
        dinput8.OrignalDirectInput8Create = GetProcAddress(dinput8.dll, "DirectInput8Create");
        dinput8.OrignalDllCanUnloadNow = GetProcAddress(dinput8.dll, "DllCanUnloadNow");
        dinput8.OrignalDllGetClassObject = GetProcAddress(dinput8.dll, "DllGetClassObject");
        dinput8.OrignalDllRegisterServer = GetProcAddress(dinput8.dll, "DllRegisterServer");
        dinput8.OrignalDllUnregisterServer = GetProcAddress(dinput8.dll, "DllUnregisterServer");
        dinput8.OrignalGetdfDIJoystick = GetProcAddress(dinput8.dll, "GetdfDIJoystick");

        telltale_hook = LoadLibrary("telltale_hook.dll");

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        FreeLibrary(dinput8.dll);
        FreeLibrary(telltale_hook);
    }
    break;
    }
    return TRUE;
}
