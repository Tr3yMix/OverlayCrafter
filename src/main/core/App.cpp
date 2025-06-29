#include "App.h"

#include <utility>

#include "ResourcePaths.h"

#include "utils/FileDialog.h"
#include "utils/WhiteTexture.h"

App::App(std::string title, const sf::Vector2<float> windowDimensions, const sf::Vector2<float> spriteScale, Theme theme)
: m_title(std::move(title)), m_windowDimensions(windowDimensions), m_spriteScale(spriteScale),
m_theme(std::move(theme)), m_imageTexture(WhiteTexture())
{
    initWindow();
    initView();
    initFont();
    initToolbar();
    initSprite();
}

App::App(): App("App", sf::Vector2f(800, 600), sf::Vector2f(16, 16), Theme::Light()){}

void App::initWindow() {
    m_window.create(sf::VideoMode(static_cast<sf::Vector2u>(m_windowDimensions)), m_title,
                  sf::Style::Default, sf::State::Windowed);

    if(sf::Image icon; icon.loadFromFile(ResourcePaths::imagePath / "logo_256x256.png")) {
        m_window.setIcon(icon);
    }else{ log(LogType::Error, "Failed to load icon image"); }
}

void App::initView() {
    m_view = std::make_unique<sf::View>(sf::FloatRect({0, 0}, m_windowDimensions));
    m_window.setView(*m_view);
}

void App::initFont() {
    if(!m_font.openFromFile(ResourcePaths::fontPath / "arial.ttf")) {
        log(LogType::Error, "Failed to load font file");
    }
}

void App::initToolbar() {
    m_toolbar = std::make_unique<Toolbar>(sf::Vector2u(m_window.getSize().x, 50), m_theme.getColors() ,m_font);
    m_toolbar->addButton("Open Texture", [this] {
        openTexture(m_imageTexture);
        m_sprite->setTexture(m_imageTexture, true);
        centerSprite();
    });
    m_toolbar->addButton("Open Pack", [this] {
        openResourcePack();
    });
}

void App::initSprite() {
    m_sprite = std::make_unique<sf::Sprite>(m_imageTexture);
    m_sprite->setScale(m_spriteScale);
    centerSprite();
}

void App::update() {

    handleEvents();

    m_window.clear(m_theme.getColors().background);

    m_window.setView(*m_view);

    m_window.draw(*m_sprite);

    m_toolbar->draw(m_window);

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
            updateViewAspectRatio(*resized);
        }
        m_toolbar->handleEvent(event, m_window);
    }
}

void App::updateViewAspectRatio(const sf::Event::Resized& event) {
    const float windowAspect = static_cast<float>(event.size.x) / static_cast<float>(event.size.y);
    const float viewAspect = m_view->getSize().x / m_view->getSize().y;

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

    m_view->setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
    m_window.setView(*m_view);

    debugf("Window size: {}x{}", m_window.getSize().x, m_window.getSize().y);

    m_toolbar->resize(sf::Vector2u(m_window.getSize().x, 50.f));
}


void App::centerSprite() const {
    const sf::Vector2f viewSize = m_view->getSize();
    const sf::FloatRect spriteBounds = m_sprite->getGlobalBounds();

    const float posX = (static_cast<float>(viewSize.x) - spriteBounds.size.x) / 2.f;
    const float posY = (static_cast<float>(viewSize.y) - spriteBounds.size.y) / 2.f;

    m_sprite->setPosition(sf::Vector2f(posX, posY));
}





