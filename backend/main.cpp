#include <drogon/drogon.h>

int main()
{
    drogon::app().setThreadNum(4);
    drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().run();
    
    return 0;
}