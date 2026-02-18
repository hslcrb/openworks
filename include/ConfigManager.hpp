#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * ConfigManager Class
 * Manages global and folder-specific instructions.
 */
class ConfigManager {
public:
    static void loadGlobalConfig(const std::string& path);
    static std::string getInstruction(const std::string& category);

private:
    static std::map<std::string, std::string> configs_;
};

#endif // CONFIG_MANAGER_HPP
