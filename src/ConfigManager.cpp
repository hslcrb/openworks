#include "ConfigManager.hpp"
#include <fstream>
#include <iostream>

std::map<std::string, std::string> ConfigManager::configs_;

void ConfigManager::loadGlobalConfig(const std::string& path) {
    try {
        std::ifstream file(path);
        if (file.is_open()) {
            json j;
            file >> j;
            for (auto& [key, value] : j.items()) {
                configs_[key] = value.get<std::string>();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() << std::endl;
    }
}

std::string ConfigManager::getInstruction(const std::string& category) {
    if (configs_.find(category) != configs_.end()) {
        return configs_[category];
    }

}
