#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * FileManager Class
 * Handles local file system operations.
 */
class FileManager {
public:
    static bool createFile(const std::string& path, const std::string& content);
    static std::string readFile(const std::string& path);
    static bool deleteFile(const std::string& path);
    static std::vector<std::string> listDirectory(const std::string& path);
};

#endif // FILE_MANAGER_HPP
