#pragma once

#include <drogon/HttpController.h>
#include <jsoncpp/json/json.h>

using namespace drogon;

class HealthController : public HttpController<HealthController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::health, "/health", Get);
    METHOD_LIST_END

    using callback = std::function<void (const HttpResponsePtr &)>;

    void health(const HttpRequestPtr &, callback &&callback);
};