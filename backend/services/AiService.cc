#include "AiService.h"

size_t AIService::write_data(void* buffer, size_t buff_size, size_t nmemb, void* userp) 
{
    std::string& text = *static_cast<std::string*>(userp);
    size_t totalsize = buff_size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

void AIService::init() 
{   
    CURL* curl;
    CURLcode resp;
    std::string result;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://router.huggingface.co/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    }

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    
    resp = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (CURLE_OK != resp)
        std::cerr << "CURL error: " << resp << "\n";

    curl_global_cleanup();

    std::cout << result << "\n";
}

std::string AIService::sendPrompt(const std::string& prompt)
{
    CURL* curl;
    curl = curl_easy_init();

    if (!curl)
    {
        std::cerr << "CURL init failed\n";
        return "CURL init failed\n";
    }

    json body;
    body["model"] = "meta-llama/Llama-3.1-8B-Instruct";
    body["stream"] = false;
    body["messages"] = json::array();
    body["messages"].push_back({
        {'role', 'user'},
        {"content", prompt}
    });

    std::string jsonBody = body.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer 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");
    
    std::string responseFromServer;

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "https://router.huggingface.co/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseFromServer);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        return "Couldn't perform the request\n";
        std::cerr << "Couldn't perform the request: " << curl_easy_strerror(res) << "\n";
    }

    long httpCode = 0;
    httpCode = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    if (httpCode != 200)
    {
        return "http code failer: " + httpCode;
        std::cerr << "http code error: " << httpCode << "\n";
    }

    if (responseFromServer.empty())
    {
        return "Response is empty\n";
        std::cerr << "Response is empty\n";
    }

    json j;
    try
    {
        j = json::parse(responseFromServer);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // Cleanup
    curl_easy_cleanup(curl);
    return j["choices"][0]["message"]["content"];
}