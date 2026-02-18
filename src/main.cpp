#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "FileManager.hpp"
#include "LLMClient.hpp"
#include "Planner.hpp"

using json = nlohmann::json;

/**
 * OpenWorks C++ Engine Main Entry Point
 * Rheehose (Rhee Creative) 2008-2026
 * License: Apache 2.0
 */

void handleRPC() {
    // Initial configuration (should come from first RPC or env)
    LLMClient llm("YOUR_API_KEY", "https://api.openai.com/v1/chat/completions");
    Planner planner(&llm);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "exit" || line.empty()) break;
        
        try {
            json request = json::parse(line);
            std::string method = request["method"];
            json params = request["params"];
            int id = request["id"];

            json response;
            response["jsonrpc"] = "2.0";
            response["id"] = id;

            if (method == "run_request") {
                std::string userRequest = params["request"];
                planner.createPlan(userRequest);
                planner.executePlan();
                response["result"] = "Plan execution completed";
            } else if (method == "list_files") {
                std::string path = params["path"];
                response["result"] = FileManager::listDirectory(path);
            } else {
                response["error"] = {{"code", -32601}, {"message", "Method not found"}};
            }
            
            std::cout << response.dump() << std::endl;
        } catch (const std::exception& e) {
            json errorResponse;
            errorResponse["jsonrpc"] = "2.0";
            errorResponse["error"] = {{"code", -32700}, {"message", e.what()}};
            std::cout << errorResponse.dump() << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command = argv[1];
        if (command == "rpc") {
            handleRPC();
            return 0;
        } else if (command == "version") {
            std::cout << "OpenWorks Engine Version 0.1.0" << std::endl;
            return 0;
        }
    }

    std::cout << "OpenWorks Engine v0.1.0 Starting..." << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Usage: openworks rpc | version" << std::endl;

    return 0;
}
