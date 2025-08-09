#pragma once
#include "NativeWindow.h"


class NativeEventHandler {

public:
    static LRESULT handleMessage(const win::WMC& ctx);

private:
    static void handleClose(const win::WMC& ctx);

    static void handleResize(const win::WMC& ctx);

    static void handleLeftMouseDown(const win::WMC& ctx);

};
