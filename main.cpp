#include "GuiBuilder.h"
#include "Controller.h"
#include <memory>
#ifdef _WIN32
    #include "WindowsController.h"
#else
    #include "LinuxController.h"
#endif

using namespace std;

int main() {
    unique_ptr<Controller> controller;

    #ifdef _WIN32
        controller = make_unique<WindowsController>();
    #else
        controller = make_unique<LinuxController>();
    #endif

    // resolution of the window appropriate for full hd (1920x1080)
    // in case of other display resolution, window will be scaled automatically
    GuiBuilder guiBuilder(350, 70, controller.get());
    guiBuilder.WindowInit();
    guiBuilder.RunGui();
    return 0;
}
