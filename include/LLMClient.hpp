#ifndef LLM_CLIENT_HPP
#define LLM_CLIENT_HPP

#include <string>
#include <vector>

/**
 * LLMClient Class
 * Handles API requests to LLM providers.
 */
class LLMClient {
public:
    struct Response {
        std::string text;
        bool success;
    };

    LLMClient(const std::string& apiKey, const std::string& endpoint);
    Response chat(const std::string& prompt);
    
    // Constrained selection logic
    std::string selectOption(const std::string& question, const std::vector<std::string>& options);

private:
    std::string apiKey_;
    std::string endpoint_;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // LLM_CLIENT_HPP
