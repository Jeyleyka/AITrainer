#include <drogon/HttpController.h>
#include <jsoncpp/json/json.h>
#include <chrono>

class HealthService
{
public:
    HealthService();
    
    bool isHealthy() const;
    Json::Value getStatus() const;

private:
    std::chrono::steady_clock::time_point startTime;
};