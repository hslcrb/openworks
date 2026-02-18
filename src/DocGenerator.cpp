#include "DocGenerator.hpp"
#include <iostream>
#include <fstream>
#include <vector>

// Note: Real OOXML generation requires zipping XML files. 
// For this prototype, we create markers or use a simplified approach.
bool DocGenerator::generateDocx(const std::string& path, const std::string& title, const std::string& content) {
    std::cout << "Generating DOCX: " << path << std::endl;
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << "DOCX_MOCK_HEADER\nTitle: " << title << "\nContent: " << content << std::endl;
    file.close();
    return true;
}

bool DocGenerator::generateXlsx(const std::string& path, const std::string& sheetName, const std::vector<std::vector<std::string>>& data) {
    std::cout << "Generating XLSX: " << path << std::endl;
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << "XLSX_MOCK_HEADER\nSheet: " << sheetName << std::endl;
    for (const auto& row : data) {
        for (const auto& cell : row) {
            file << cell << ",";
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool DocGenerator::generatePptx(const std::string& path, const std::string& title, const std::string& subtitle) {
    std::cout << "Generating PPTX: " << path << std::endl;
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << "PPTX_MOCK_HEADER\nTitle: " << title << "\nSubtitle: " << subtitle << std::endl;
    file.close();
    return true;
}
