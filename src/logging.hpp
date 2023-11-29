#pragma once

#include <string>

namespace telltale_hook::log {
    // Deletes log.txt from the game directory
    void remove_previous_log();

    // Logs without a trailing newline
    void log(std::string);

    // Logs with a trailing newline
    void logln(std::string);

    void log_v2(std::string format, ...);
}