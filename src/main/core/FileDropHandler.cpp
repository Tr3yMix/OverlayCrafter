
#include "FileDropHandler.h"

std::function<void(const std::string&)> FileDropHandler::s_onDropCallback;

WNDPROC FileDropHandler::s_originalWndProc = nullptr;

FileDropHandler::FileDropHandler(HWND hwnd): m_hwnd(hwnd) {
    DragAcceptFiles(hwnd, TRUE);
    s_originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
}

void FileDropHandler::setOnDropCallback(const std::function<void(const std::string &)>& callback) {
    s_onDropCallback = callback;
}

LRESULT FileDropHandler::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
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



