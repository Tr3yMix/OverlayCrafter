#include "App.h"

#include <utility>

#include "ResourcePaths.h"

#include "utils/FileDialog.h"
#include "utils/JarReader.h"
#include "utils/ProjectFile.h"
#include "utils/WhiteTexture.h"

App::App(std::string title, const sf::Vector2<float> windowDimensions, const sf::Vector2<float> spriteScale, Theme theme)
: m_title(std::move(title)), m_initWindowSize(windowDimensions), m_spriteScale(spriteScale),
m_theme(std::move(theme)), m_imageTexture(WhiteTexture())
{
    initWindow();
    initViews();
    initFont();
    initToolbar();
    initSprite();
}

App::App(): App("App", sf::Vector2f(800, 600), sf::Vector2f(16, 16), Theme::Light()){}

void App::initWindow() {
    m_window.create(
        sf::VideoMode(static_cast<sf::Vector2u>(m_initWindowSize)),
        m_title,
        sf::Style::None
        );

    if(sf::Image icon; icon.loadFromFile(ResourcePaths::imagePath / "logo_256x256.png")) {
        m_window.setIcon(icon);
    }else{ log(Logger::LogType::Error, "Failed to load icon image"); }

    HWND hwnd = m_window.getNativeHandle();
    m_dragHandler = std::make_unique<DragAndDropHandler>(hwnd);
    m_dragHandler->setOnDropCallback([this](const std::string& filePath) {
        if(!m_imageTexture.loadFromFile(filePath)) {
            log(Logger::LogType::Error, "Failed to load dropped image");
        }
    });
}

void App::initViews() {
    auto defRect = sf::FloatRect({0, 0}, m_initWindowSize);

    m_mainView = std::make_unique<sf::View>(defRect);
    m_window.setView(*m_mainView);

    m_topView = std::make_unique<sf::View>(defRect);
    m_leftView = std::make_unique<sf::View>(defRect);
    m_rightView = std::make_unique<sf::View>(defRect);
}

void App::initFont() {
    if(!m_font.openFromFile(ResourcePaths::fontPath / "arial.ttf")) {
        log(Logger::LogType::Error, "Failed to load font file");
    }
}

void App::initToolbar() {
    m_menubar = std::make_unique<MenuBar>(MenuType::Horizontal,sf::Vector2u(m_window.getSize().x, 35), m_theme.getColors() ,m_font);
    m_menubar->addButton("List Mod", [this] {
        JarReader::listJarContents((ResourcePaths::modPath / "create-1.20.1-6.0.6.jar").string());
    });
    m_menubar->addButton("New Project", [this]{Logger::debug("Created New Project!");});
    m_menubar->addButton("Open Project", [this] {ProjectFile::load(m_imageTexture);});
    m_menubar->addButton("Save Project", [this] {ProjectFile::save(m_imageTexture);});
    m_menubar->addButton("Open Texture", [this] {
        FileDialog::openTexture(m_imageTexture);
        m_sprite->setTexture(m_imageTexture, true);
        centerSprite();
    });
    m_menubar->addButton("Open Pack", [this] {
        FileDialog::openResourcePack();
    });
    m_menubar->addButton("Apply Mask", [this] {
        FileDialog::generateMaskFromTexture(m_imageTexture);
        m_sprite->setTexture(m_imageTexture, true);
        centerSprite();
    });

    m_button = std::make_unique<Button>(ButtonType::Critical,
        sf::Vector2f(static_cast<float>(m_window.getSize().x) - 35.f, 0),\
        sf::Vector2f(35, 35), m_font, "Exit", m_theme.getColors(), [this]{m_window.close();});
}

void App::initSprite() {
    m_sprite = std::make_unique<sf::Sprite>(m_imageTexture);
    m_sprite->setScale(m_spriteScale);
    centerSprite();
}

void App::update() {

    handleEvents();

    m_window.clear(m_theme.getColors().background);

    m_window.setView(*m_mainView);
    m_window.draw(*m_sprite);


    //Draw Top Elements

    m_menubar->draw(m_window, *m_topView, *m_leftView);


    //Draw Right Elements

    m_window.setView(*m_rightView);
    m_button->draw(m_window);

    m_window.display();
}

void App::handleEvents() {

    while(const std::optional<sf::Event> event = m_window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
            m_window.close();
        }
        else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if(key->scancode == sf::Keyboard::Scancode::Escape) {
                m_window.close();
            }
        }else if(const auto* resized = event->getIf<sf::Event::Resized>()) {
            updateViewportsOnResize(*resized);

        }else if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if(mousePressed->button == sf::Mouse::Button::Left) {
                if(GetCursorPos(&m_dragMouseStartPos)) {
                    RECT rect;
                    if(GetWindowRect(m_window.getNativeHandle(), &rect)) {
                        m_dragWindowStartPos.x = rect.left;
                        m_dragWindowStartPos.y = rect.top;

                        if(m_dragMouseStartPos.y >= rect.top && m_dragMouseStartPos.y <= rect.top + 35) {
                            m_draggingWindow = true;
                        }
                    }
                }
            }
        }else if(const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if(mouseReleased->button == sf::Mouse::Button::Left) {
                m_draggingWindow = false;
            }
        }else if(event->is<sf::Event::MouseMoved>()) {
            if(m_draggingWindow) {
                POINT currentMousePos;
                if(GetCursorPos(&currentMousePos)) {
                    const int dx = currentMousePos.x - m_dragMouseStartPos.x;
                    const int dy = currentMousePos.y - m_dragMouseStartPos.y;

                    // ReSharper disable once CppLocalVariableMayBeConst
                    HWND hwnd = m_window.getNativeHandle();
                    SetWindowPos(
                        hwnd,
                        nullptr,
                        m_dragWindowStartPos.x + dx,
                        m_dragWindowStartPos.y + dy,
                        0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                }

            }
        }
        m_menubar->handleButtonEvents(event, m_window, *m_leftView);
        m_button->handleEvent(event, m_window, *m_rightView);
    }
}



void App::updateTopView() const {
    m_topView->setViewport(sf::FloatRect({0, 0}, {1.f, 1.f}));
}

void App::updateRightView(const sf::Event::Resized& event) const {
    const float windowAspect = static_cast<float>(event.size.x) / static_cast<float>(event.size.y);
    const float viewAspect = m_rightView->getSize().x / m_rightView->getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;

    if(windowAspect > viewAspect) {
        sizeX = viewAspect / windowAspect;
    }else {
        sizeY = windowAspect / viewAspect;
    }

    m_rightView->setViewport(sf::FloatRect({0, 0}, {sizeX, sizeY}));
}

void App::updateLeftView(const sf::Event::Resized& event) const {
    const float windowAspect = static_cast<float>(event.size.x) / static_cast<float>(event.size.y);
    const float viewAspect = m_leftView->getSize().x / m_leftView->getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;

    if(windowAspect > viewAspect) {
        sizeX = viewAspect / windowAspect;
    }else {
        sizeY = windowAspect / viewAspect;
    }

    m_leftView->setViewport(sf::FloatRect({1.f - sizeX, sizeY}, {sizeX, sizeY}));

}

void App::updateViewportsOnResize(const sf::Event::Resized& event) const {


    const float windowAspect = static_cast<float>(event.size.x) / static_cast<float>(event.size.y);
    const float viewAspect = m_mainView->getSize().x / m_mainView->getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if(windowAspect > viewAspect) {
        sizeX = viewAspect / windowAspect;
        posX = (1.f - sizeX) / 2.f;
    }else {
        sizeY = windowAspect / viewAspect;
        posY = (1.f - sizeY) / 2.f;
    }

    m_mainView->setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));

    updateTopView();
    updateLeftView(event);
    updateRightView(event);
}




void App::centerSprite() const {
    const sf::Vector2f viewSize = m_mainView->getSize();
    const sf::FloatRect spriteBounds = m_sprite->getGlobalBounds();

    const float posX = (static_cast<float>(viewSize.x) - spriteBounds.size.x) / 2.f;
    const float posY = (static_cast<float>(viewSize.y) - spriteBounds.size.y) / 2.f;

    m_sprite->setPosition(sf::Vector2f(posX, posY));
}
