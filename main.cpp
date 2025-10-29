#include "GuiBuilder.h"

int main() {
    GuiBuilder guiBuilder(400, 100);
    guiBuilder.WindowInit();
    guiBuilder.RunGui();
    return 0;
}
