#include "HealthController.h"

void HealthController::health(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)> && callback) 
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("OK");
    callback(resp);
}