#ifndef WINDOWSCONTROLLER_H
#define WINDOWSCONTROLLER_H

#include "Controller.h"

class WindowsController final : public Controller {
private:
    void FreezeScreen() override;
    void ExtractColors(void* pixel) override;

public:
    void PickPixel() override;
    void CopyToClipboard(std::string copyString) override;
};



#endif //WINDOWSCONTROLLER_H
