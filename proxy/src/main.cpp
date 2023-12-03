#include <Windows.h>
#include <filesystem>

static HMODULE telltale_hook = nullptr;

static HMODULE dll = nullptr;

typedef HRESULT(__stdcall *DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);

DirectInput8Create_t OriginalDirectInput8Create = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    char path[MAX_PATH];
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 13), "\\dinput8.dll", 14);
        dll = LoadLibrary(path);
        if (dll == NULL)
        {
            MessageBox(0, "Cannot load original dinput8.dll library", "Proxy", MB_ICONERROR);
            ExitProcess(0);
        }
        OriginalDirectInput8Create = reinterpret_cast<DirectInput8Create_t>(GetProcAddress(dll, "DirectInput8Create"));
        
        telltale_hook = LoadLibrary("telltale_hook.dll");

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        FreeLibrary(dll);
        FreeLibrary(telltale_hook);
    }
    break;
    }
    return TRUE;
}
extern "C" {
  __declspec(dllexport) HRESULT DirectInput8Create(HINSTANCE a1, DWORD a2, REFIID a3, LPVOID * a4, LPUNKNOWN a5) {
    return OriginalDirectInput8Create(a1, a2, a3, a4, a5);
  }
}