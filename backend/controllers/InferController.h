#pragma once

#include <drogon/HttpController.h>
#include <jsoncpp/json/json.h>

using namespace drogon;

class InferController : public HttpController<InferController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(InferController::infer, "/infer", Post);
    METHOD_LIST_END

    void infer(const HttpRequestPtr& req,
               std::function<void (const HttpResponsePtr &)> &&callback);
};