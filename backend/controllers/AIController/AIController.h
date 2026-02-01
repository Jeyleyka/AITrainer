#pragma once

#include <drogon/HttpController.h>
#include "../../services/HealthService/HealthService.h"

using namespace drogon;

class AIController : public HttpController<AIController>
{
public:
    AIController() = default;

    void chat(const HttpRequestPtr &, std::function<void(const HttpResponsePtr &)> &&callback);

private:
    HealthService healthService;
};