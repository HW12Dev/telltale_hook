#include "telltale_hook.hpp"
#include "lua/tthook_lua.hpp"

#include <string>
#include <iostream>
#include "logging.hpp"

#define _T(str) str

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM)
{
    CHAR title[1024];
    GetWindowText(hwnd, title, 1024);

    if (std::string(title) == std::string(_T("Telltale Games")))
    {
        telltale_hwnd = hwnd;
        return FALSE;
    }
    return TRUE;
}

void telltale_hook::setup()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    telltale_hook::log::remove_previous_log();

    telltale_hook::log::log("Starting telltale_hook with game: ");
    telltale_hook::log::logln(get_current_game());

    lua::setup_lua();
    
    //while (telltale_hwnd == NULL)
    //{
    //    EnumWindows(EnumWindowsProc, NULL);
    //    Sleep(100);
    //}

    //std::cout << telltale_hwnd << std::endl;

}

/** Get the name of the current game
 * Only contains the games currently supported by telltale_hook
*/
std::string telltale_hook::get_current_game() {
#ifdef GAME_THRONES
    return "Thrones";
#endif
#ifdef GAME_MINECRAFTSTORYMODE
    return "MinecraftStoryMode";
#endif
#ifdef GAME_TWDDS_GAMEAPP
    return "GameApp";
#endif
#ifdef GAME_TWDDS
    return "WDC";
#endif
}