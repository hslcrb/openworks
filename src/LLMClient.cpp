#include "LLMClient.hpp"
#include <curl/curl.h>
#include <iostream>

LLMClient::LLMClient(const std::string& apiKey, const std::string& endpoint)
    : apiKey_(apiKey), endpoint_(endpoint) {}

size_t LLMClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

LLMClient::Response LLMClient::chat(const std::string& prompt) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = "Authorization: Bearer " + apiKey_;
        headers = curl_slist_append(headers, authHeader.c_str());

        // Simple JSON payload (placeholder for real provider format)
        std::string payload = "{\"model\": \"gpt-4\", \"messages\": [{\"role\": \"user\", \"content\": \"" + prompt + "\"}]}";

        curl_easy_setopt(curl, CURLOPT_URL, endpoint_.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            return {readBuffer, true};
        }
    }
    return {"", false};
}

std::string LLMClient::selectOption(const std::string& question, const std::vector<std::string>& options) {
    std::string prompt = question + "\nSelect one of the following options (return only the option index):\n";
    for (size_t i = 0; i < options.size(); ++i) {
        prompt += std::to_string(i) + ". " + options[i] + "\n";
    }
    
    // Logic to force objective selection via prompting and post-processing
    Response resp = chat(prompt);
    // Simple parsing logic (placeholder)
    try {
        int index = std::stoi(resp.text);
        if (index >= 0 && index < options.size()) {
            return options[index];
        }
    } catch (...) {}
    
    return "Error: Could not determine selection";
}
