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

        // Use nlohmann/json for robust payload creation
        json payloadJson;
        payloadJson["model"] = "gpt-4";
        payloadJson["messages"] = json::array({
            {{"role", "user"}, {"content", prompt}}
        });
        payloadJson["temperature"] = 0.7;

        std::string payload = payloadJson.dump();

        curl_easy_setopt(curl, CURLOPT_URL, endpoint_.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if (res == CURLE_OK) {
            return {readBuffer, true};
        }
    }
    return {"", false};
}

std::string LLMClient::selectOption(const std::string& question, const std::vector<std::string>& options) {
    int retries = 3;
    while (retries--) {
        std::string prompt = "### QUESTION\n" + question + "\n\n### OPTIONS\n";
        for (size_t i = 0; i < options.size(); ++i) {
            prompt += std::to_string(i) + ": " + options[i] + "\n";
        }
        prompt += "\nRespond ONLY with the index number of the chosen option.";
        
        Response resp = chat(prompt);
        if (resp.success) {
            try {
                std::string cleanText = resp.text;
                size_t firstDigit = cleanText.find_first_of("0123456789");
                if (firstDigit != std::string::npos) {
                    int index = std::stoi(cleanText.substr(firstDigit));
                    if (index >= 0 && index < (int)options.size()) {
                        return options[index];
                    }
                }
            } catch (...) {}
        }
    }
    return "Error: Exceeded retries for consistent selection";
}
