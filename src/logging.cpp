#include "logging.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

#include <stdarg.h>

void telltale_hook::log::log(std::string tolog) {
    std::cout << tolog;
    std::ofstream logfile("log.txt", std::ios_base::app);
    logfile << tolog;
    logfile.close();
}

void telltale_hook::log::logln(std::string tolog) {
    std::cout << tolog << std::endl;
    std::ofstream logfile("log.txt", std::ios_base::app);
    logfile << tolog << "\n";
    logfile.close();
}

void telltale_hook::log::remove_previous_log() {
    std::filesystem::path log_path{"log.txt"};
    std::filesystem::remove(log_path);
}