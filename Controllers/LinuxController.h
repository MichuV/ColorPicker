#ifndef LINUXCONTROLLER_H
#define LINUXCONTROLLER_H

#include "Controller.h"
#include <X11/Xlib.h>

class LinuxController final : public Controller {
private:
    void ExtractColors(void* pixel) override;
    Window CreateOverlay(Display* display, Window root);

public:
    void PickPixel() override;
    void CopyToClipboard(std::string copyString) override;
};



#endif //LINUXCONTROLLER_H
