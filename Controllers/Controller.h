#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

class Controller {
  protected:
    int r, g, b;
    virtual void FreezeScreen() = 0;
    virtual void ExtractColors(void* pixel) = 0;

  public:
    Controller() : r(0), g(0), b(0) {}
    virtual void PickPixel() = 0;
    virtual void CopyToClipboard(std::string copyString) = 0;
    virtual ~Controller() = default;
};

#endif //CONTROLLER_H
