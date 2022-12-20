#include "crow.h"
#include "webgui.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
        ([]() {
        return "Hello, world!";
            });

    webGui(18080).run();

    app.port(18080).run();
}
