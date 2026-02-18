#include "SafetyApprover.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool SafetyApprover::requestApproval(const std::string& action) {
    json request;
    request["jsonrpc"] = "2.0";
    request["method"] = "request_approval";
    request["params"] = {{"action", action}};
    request["id"] = 999; // Internal ID for safety checks

    std::cout << request.dump() << std::endl;

    std::string responseLine;
    if (std::getline(std::cin, responseLine)) {
        try {
            json response = json::parse(responseLine);
            return response["result"].get<bool>();
        } catch (...) {}
    }
    return false;
}

SafetyApprover::Permission SafetyApprover::getPolicy(const std::string& action) {
    // Basic policy logic (could be loaded from file)
    if (action.find("delete") != std::string::npos) return Permission::ASK;
    return Permission::ALLOW;
}
