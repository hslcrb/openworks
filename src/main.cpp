#include <iostream>
#include <string>
#include <vector>
#include "FileManager.hpp"
#include "LLMClient.hpp"

/**
 * OpenWorks C++ Engine Main Entry Point
 * Rheehose (Rhee Creative) 2008-2026
 * License: Apache 2.0
 */

void handleRPC() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "exit") break;
        // Basic RPC echo for now
        std::cout << "{\"jsonrpc\": \"2.0\", \"result\": \"Echo: " << line << "\", \"id\": 1}" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command = argv[1];
        if (command == "rpc") {
            handleRPC();
            return 0;
        } else if (command == "version") {
            std::cout << "OpenWorks Engine Version 0.0.0" << std::endl;
            return 0;
        }
    }

    std::cout << "OpenWorks Engine v0.0.0 Starting..." << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Usage: openworks rpc | version" << std::endl;

    return 0;
}
