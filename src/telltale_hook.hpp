#pragma once

#include <Windows.h>
#include <string>

// GLOBALS

static HWND telltale_hwnd = NULL;


namespace telltale_hook {
    std::string get_current_game();
    void setup();
}