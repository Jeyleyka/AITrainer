#include "HealthService.h"

HealthService::HealthService()
    :
    startTime(std::chrono::steady_clock::now())
{}

bool HealthService::isHealthy() const
{
    // Temporary
    return true;
}

Json::Value HealthService::getStatus() const
{
    Json::Value status;
    status["status"] = isHealthy() ? "ok" : "unhealthy";

    auto uptime = std::chrono::steady_clock::now() - startTime;
    status["uptime_sec"] = static_cast<Json::UInt64>(std::chrono::duration_cast<std::chrono::seconds>(uptime).count());

    return status;
}