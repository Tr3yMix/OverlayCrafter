#pragma once

#include <memory>
#include <windows.h>

#include "math/Vector2.h"
#include "platform/windows/NativeWindow.h"
#include "ui/Drawable.h"
#include "ui/DrawTarget.h"


class AppWindow final : public ui::DrawTarget{

public:

    AppWindow(math::Vector2u windowSize, LPCSTR title, HINSTANCE hInstance);

    void draw(ui::Drawable& drawable) const override;

    std::unique_ptr<win::NativeWindow> m_nativeWindow;

    void update() const;

    [[nodiscard]] HDC getDC() const;

    [[nodiscard]] bool isRunning() const;


private:


};

