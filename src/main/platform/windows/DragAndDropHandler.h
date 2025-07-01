
#pragma once

#include <functional>
#include <string>
#include <windows.h>


class DragAndDropHandler {
public:
    explicit DragAndDropHandler(HWND hwnd);

    void setOnDropCallback(const std::function<void(const std::string&)>& callback);

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    static WNDPROC s_originalWndProc;


    static std::function<void(const std::string&)> s_onDropCallback;
    HWND m_hwnd;
};

