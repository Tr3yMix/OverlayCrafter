
#include "DragAndDropHandler.h"


std::function<void(const std::string&)> DragAndDropHandler::s_onDropCallback;

WNDPROC DragAndDropHandler::s_originalWndProc = nullptr;

// ReSharper disable once CppParameterMayBeConst
DragAndDropHandler::DragAndDropHandler(HWND hwnd) : m_hwnd(hwnd) {
    DragAcceptFiles(hwnd, TRUE);
    s_originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DragAndDropHandler::WndProc)));

}

// ReSharper disable once CppMemberFunctionMayBeStatic
void DragAndDropHandler::setOnDropCallback(const std::function<void(const std::string &)> &callback) {
    s_onDropCallback = callback;
}

// ReSharper disable once CppParameterMayBeConst
LRESULT DragAndDropHandler::WndProc(HWND hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam) {
    if(message == WM_DROPFILES) {

        const auto hDrop = reinterpret_cast<HDROP>(wParam);

        char path[MAX_PATH];
        DragQueryFileA(hDrop, 0, path, MAX_PATH);
        DragFinish(hDrop);

        if(s_onDropCallback) {
            s_onDropCallback(std::string(path));
        }
        return 0;
    }

    return CallWindowProc(s_originalWndProc, hwnd, message, wParam, lParam);
}

