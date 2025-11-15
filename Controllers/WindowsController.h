#ifndef WINDOWSCONTROLLER_H
#define WINDOWSCONTROLLER_H

#include "Controller.h"
#include <windows.h>

class WindowsController final : public Controller {
private:
    void ExtractColors(void* pixel) override;
    HWND CreateOverlay();
public:
    void PickPixel() override;
    void CopyToClipboard(std::string copyString) override;
};



#endif //WINDOWSCONTROLLER_H
