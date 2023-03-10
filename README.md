# cppwebgui
Create js desktop applications with cpp web server


## Usage with webgui

```c++
#include "webgui.h"

int main(){
    webGui(port).run();
}
```

Following application using [crow](https://github.com/CrowCpp/Crow) :
```c++
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
```

# Thanks

- [flaskwebgui](https://github.com/ClimenteA/flaskwebgui)
- [tiny-process-library](https://github.com/eidheim/tiny-process-library)
- [crow](https://github.com/CrowCpp/Crow)
