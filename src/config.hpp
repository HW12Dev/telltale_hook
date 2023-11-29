#pragma once

#include <string>
#include <json.hpp>

namespace telltale_hook::config {
    void load_config();
    void save_config();
    template<typename T> T get_value(std::string name);
    template<typename T> void set_value(std::string name, T value);
}