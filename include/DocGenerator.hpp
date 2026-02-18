#ifndef DOC_GENERATOR_HPP
#define DOC_GENERATOR_HPP

#include <string>
#include <vector>

/**
 * DocGenerator Class
 * Handles generation of DOCX, XLSX, and PPTX files.
 */
class DocGenerator {
public:
    static bool generateDocx(const std::string& path, const std::string& title, const std::string& content);
    static bool generateXlsx(const std::string& path, const std::string& sheetName, const std::vector<std::vector<std::string>>& data);
    static bool generatePptx(const std::string& path, const std::string& title, const std::string& subtitle);
};

#endif // DOC_GENERATOR_HPP
