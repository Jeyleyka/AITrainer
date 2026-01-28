#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

using json = nlohmann::json;

// HuggyFace токен - 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

class AIService
{
public:
    void init();
    std::string sendPrompt(const std::string& prompt);

private:
    static size_t write_data(void* buffer, size_t buff_size, size_t nmemb, void* userp);
};