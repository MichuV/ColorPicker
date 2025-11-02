#include "WindowsController.h"
#include <iostream>
#include <windows.h>

void WindowsController::ExtractColors(void *pixel) {
    auto* colorPixel = static_cast<COLORREF*>(pixel);
    r = GetRValue(*colorPixel);
    g = GetGValue(*colorPixel);
    b = GetBValue(*colorPixel);
}

HWND WindowsController::CreateOverlay() {
    int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int width  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    HWND overlay = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        "STATIC",
        nullptr,
        WS_POPUP,
        x ,y, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr
    );

    SetLayeredWindowAttributes(overlay, 0, 1, LWA_ALPHA);
    ShowWindow(overlay, SW_SHOW);
    SetCursor(LoadCursor(nullptr, IDC_CROSS));

    return overlay;
}

void WindowsController::PickPixel() {
    HWND hwnd = GetActiveWindow();
    ShowWindow(hwnd, SW_HIDE);
    HWND overlay = CreateOverlay();

    while (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
        Sleep(10);

    POINT point;
    GetCursorPos(&point);

    HDC hdc = GetDC(nullptr);
    COLORREF pixel = GetPixel(hdc, point.x, point.y);
    ReleaseDC(nullptr, hdc);

    ExtractColors(&pixel);

    DestroyWindow(overlay);
    ShowWindow(hwnd, SW_SHOW);
}

void WindowsController::CopyToClipboard(std::string copyString) {
    if (!OpenClipboard(nullptr)) return;

    EmptyClipboard();
    size_t size = copyString.length() + 1;

    if (HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE, size)) {
        memcpy(GlobalLock(hMem), copyString.c_str(), size);
        GlobalUnlock(hMem);
        if (!SetClipboardData(CF_TEXT, hMem))
            GlobalFree(hMem);
    }

    CloseClipboard();
}
