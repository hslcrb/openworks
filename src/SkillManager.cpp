#include "SkillManager.hpp"
#include <iostream>

std::string SkillManager::runMCP(const std::string& service, const std::string& action) {
    std::cout << "[SkillManager] Executing MCP: " << service << " - " << action << std::endl;
    // Mock response
    return "{\"status\": \"success\", \"message\": \"MCP action executed\"}";
}

std::string SkillManager::runBrowser(const std::string& url, const std::string& action) {
    std::cout << "[SkillManager] Executing Browser Action: " << url << " - " << action << std::endl;
    // Mock response
    return "{\"status\": \"success\", \"data\": \"Scraped content from browser\"}";
}
