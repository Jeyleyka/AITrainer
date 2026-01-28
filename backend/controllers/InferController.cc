#include "InferController.h"

void InferController::infer(const HttpRequestPtr& req,
                            std::function<void (const HttpResponsePtr &)>&& callback)
{
    auto json = req->getJsonObject();

    // Get JSON
    if (!json)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Invalid JSON");
        callback(resp);
        return;
    }

    // Get data
    std::string text = (*json)["text"].asString();

    // Form an answer
    Json::Value res;
    res["status"] = "ok";
    res["input"] = text;
    res["prediction"] = "stub";

    auto resp = HttpResponse::newHttpJsonResponse(res);
    callback(resp);
}