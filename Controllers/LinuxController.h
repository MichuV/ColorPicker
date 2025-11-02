#ifndef LINUXCONTROLLER_H
#define LINUXCONTROLLER_H

#include "Controller.h"

class LinuxController final : public Controller {
private:
    void ExtractColors(void* pixel) override;

public:
    void PickPixel() override;
    void CopyToClipboard(std::string copyString) override;
};



#endif //LINUXCONTROLLER_H
