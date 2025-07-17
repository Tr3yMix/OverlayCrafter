#pragma once

#include <functional>
#include <windows.h>
#include <string>

class FileDropHandler {

public:
    explicit FileDropHandler(HWND hwnd);

    void setOnDropCallback(const std::function<void(const std::string&)>& callback);

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static WNDPROC s_originalWndProc;

    static std::function<void(const std::string&)> s_onDropCallback;
    HWND m_hwnd;

};

