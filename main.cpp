#include "GuiBuilder.h"

int main() {
    // resolution of the window appropriate for full hd (1920x1080)
    // in case of other display resolution, window will be scaled automatically
    GuiBuilder guiBuilder(400, 100);
    guiBuilder.WindowInit();
    guiBuilder.RunGui();
    return 0;
}
