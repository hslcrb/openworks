#include "FileManager.hpp"
#include <fstream>
#include <iostream>

bool FileManager::createFile(const std::string& path, const std::string& content) {
    try {
        std::ofstream file(path);
        if (file.is_open()) {
            file << content;
            file.close();
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error creating file: " << e.what() << std::endl;
    }
    return false;
}

std::string FileManager::readFile(const std::string& path) {
    std::string content;
    try {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                content += line + "\n";
            }
            file.close();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << std::endl;
    }
    return content;
}

bool FileManager::deleteFile(const std::string& path) {
    try {
        return fs::remove(path);
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
    return false;
}

std::vector<std::string> FileManager::listDirectory(const std::string& path) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            files.push_back(entry.path().string());
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing directory: " << e.what() << std::endl;
    }
    return files;
}
