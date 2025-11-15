#include "LinuxController.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <iostream>
#include <X11/Xutil.h>

void LinuxController::ExtractColors(void *pixel) {
    auto* colorPixel = static_cast<unsigned long* >(pixel);
    r = (*colorPixel >> 16) & 0xFF;
    g = (*colorPixel >> 8) & 0xFF;
    b = (*colorPixel >> 0) & 0xFF;
}

Window LinuxController::CreateOverlay(Display *display, Window root) {
    XWindowAttributes rootAttributes;
    XGetWindowAttributes(display, root, &rootAttributes);

    XSetWindowAttributes windowAttributes;
    windowAttributes.override_redirect = true;
    int screen = DefaultScreen(display);

    Window overlay = XCreateWindow(display, root, 0, 0, rootAttributes.width, rootAttributes.height, 0,
        DefaultDepth(display, screen), CopyFromParent, DefaultVisual(display, screen),
        CWOverrideRedirect, &windowAttributes);

    Cursor cursor = XCreateFontCursor(display, XC_crosshair);
    XDefineCursor(display, overlay, cursor);

    XSelectInput(display, overlay, ButtonPressMask);
    XMapRaised(display, overlay);
    XFlush(display);
    XGrabPointer(display, overlay, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, overlay, None, CurrentTime);
    return overlay;
}

void LinuxController::PickPixel() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) return;

    Window root = DefaultRootWindow(display);
    Window overlay = CreateOverlay(display, root);

    XEvent event;
    XButtonEvent xbuttonEvent;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == ButtonPress && event.xbutton.button == Button1) {
            xbuttonEvent = event.xbutton;
            break;
        }
    }

    XImage* img = XGetImage(display, root, xbuttonEvent.x_root, xbuttonEvent.y_root, 1, 1, AllPlanes, ZPixmap);
    unsigned long pixel = XGetPixel(img, 0, 0);
    ExtractColors(&pixel);
    XDestroyImage(img);
    XUngrabPointer(display, CurrentTime);
    XDestroyWindow(display, overlay);
    XFlush(display);
    XCloseDisplay(display);
}

void LinuxController::CopyToClipboard(std::string copyString) {
    FILE* pipe = popen("xclip -selection clipboard -i", "w");
    if (pipe) {
        fwrite(copyString.c_str(), 1, copyString.length(), pipe);
        pclose(pipe);
    } else {
        std::cerr << "xclip required to copy values" << std::endl;
    }
}
