#include "AIController.h"

void AIController::chat(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    if (!healthService.isHealthy())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k503ServiceUnavailable);
        resp->setBody("Server unhealthy, try later");
        callback(resp);
        return;
    }
}