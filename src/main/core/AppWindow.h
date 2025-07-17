#pragma once

#include <GL/gl.h>
#include <windows.h>

#include "ui/Drawable.h"
#include "utils/Color.h"


class AppWindow {

public:

    void createWindow(int width, int height, LPCSTR title);
    void createOpenGLContext();
    void messageLoop() const;
    void cleanup() const;

    HINSTANCE m_hInstance;
    HWND m_hwnd;

private:


    HDC m_hdc;
    HGLRC m_hglrc;
    bool running = true;


    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    LRESULT handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


    void draw(const ui::Drawable& drawable) const;

    static void clear(util::Color color);
    void display() const;


};

