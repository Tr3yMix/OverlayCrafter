
#include "NativeEventHandler.h"

#include <GL/gl.h>


LRESULT NativeEventHandler::handleMessage(const win::WMC& ctx) {
    switch (ctx.msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(ctx.hwnd, &ps);
            EndPaint(ctx.hwnd, &ps);
            break;
        }
        case WM_SIZE: {
            handleResize(ctx);
            break;
        }
        case WM_LBUTTONDOWN: {
            handleLeftMouseDown(ctx);
            break;
        }
        case WM_CLOSE: {
            handleClose(ctx);
            break;
        }
        case WM_DESTROY: break;
        default: return DefWindowProc(ctx.hwnd, ctx.msg, ctx.wParam, ctx.lParam);
    }
    return 0;
}

void NativeEventHandler::handleResize(const win::WMC& ctx){
    ctx.window->m_width = static_cast<math::Uint>(LOWORD(ctx.lParam));
    ctx.window->m_height = static_cast<math::Uint>(HIWORD(ctx.lParam));
    glViewport(0, 0, ctx.window->m_width.signedInt(), ctx.window->m_height.signedInt());
}

void NativeEventHandler::handleLeftMouseDown(const win::WMC& ctx){
    if (const int yPos = HIWORD(ctx.lParam); yPos <= 40) {
        ReleaseCapture();
        SendMessage(ctx.hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
}


void NativeEventHandler::handleClose(const win::WMC& ctx) {
    ctx.window->m_isRunning = false;
    PostQuitMessage(0);
}
