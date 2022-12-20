#include "crow.h"
#include "webgui.h"

int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base("./templates");

    CROW_ROUTE(app, "/")
        ([] {
        crow::mustache::context ctx;
        return crow::mustache::load("index.html").render();
            });

    CROW_ROUTE(app, "/home")
        ([] {
        crow::mustache::context ctx;
        return crow::mustache::load("some_page.html").render();
            });

    webGui(18080).run();

    app.port(18080).run();
}
