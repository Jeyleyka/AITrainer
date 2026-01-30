#include "httplib.h"
#include "./services/AiService.h"

AIService service;

int main()
{
    httplib::Server svr;

    svr.Post("/prompt", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << "=== Request received ===\n";
        std::cout << "Method: POST\n";
        std::cout << "Path: " << req.path << "\n";
        std::cout << "Body:\n" << req.body << "\n";

        try
        {
            json body = json::parse(req.body);
            std::string prompt = body["prompt"];

            std::string aiResponse = service.sendPrompt(prompt);

            json response;
            response["response"] = aiResponse;

            res.set_content(response.dump(), "application/json");
        }
        catch(const std::exception& e)
        {
            res.status = 400;
            res.set_content(
                std::string("Bad request: ") + e.what(),
                "text/plain"
            );
        }
        
    });

    std::cout << "Backend running on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}