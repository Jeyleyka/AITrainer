#include "HealthController.h"

void HealthController::health(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)> && callback) 
{
    Json::Value status = healthService.getStatus();
    auto resp = HttpResponse::newHttpJsonResponse(status);
    resp->setStatusCode(k200OK);
    callback(resp);
}