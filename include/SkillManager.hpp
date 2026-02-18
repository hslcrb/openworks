#ifndef SKILL_MANAGER_HPP
#define SKILL_MANAGER_HPP

#include <string>

/**
 * SkillManager Class
 * Manages external skills like MCP and Browser automation (mote/placeholder).
 */
class SkillManager {
public:
    static std::string runMCP(const std::string& service, const std::string& action);
    static std::string runBrowser(const std::string& url, const std::string& action);
};

#endif // SKILL_MANAGER_HPP
