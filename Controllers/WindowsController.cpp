#include "WindowsController.h"
#include <iostream>
#include <windows.h>

void WindowsController::FreezeScreen() {

}

void WindowsController::ExtractColors(void *pixel) {
    //COLORREF* colorPixel = static_cast<COLORREF*>(pixel);
}

void WindowsController::PickPixel() {

}

void WindowsController::CopyToClipboard(std::string copyString) {
    if (!OpenClipboard(nullptr)) return;

    EmptyClipboard();
    const int size = copyString.length() + 1;

    if (const HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE, size)) {
        memcpy(GlobalLock(hMem), copyString.c_str(), size);
        GlobalUnlock(hMem);
        if (!SetClipboardData(CF_TEXT, hMem))
            GlobalFree(hMem);
    }

    CloseClipboard();
}
