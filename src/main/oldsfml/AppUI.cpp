#include "AppUI.h"
#include "OldWindow.h"
#include "util/FileDialog.h"
#include "util/JarReader.h"
#include "util/ProjectFile.h"


AppUI::AppUI(OldWindow& window, const sf::Vector2f& spriteScale, Theme theme): m_texture(whiteTexture()), m_window(window), m_theme(std::move(theme)) {

    if(!m_font.openFromFile(ResourcePaths::fontPath / "arial.ttf")) {
        log(Logger::LogType::Error, "Failed to load font file");
    }



    m_menuBar = std::make_unique<ButtonBar>(MenuType::Horizontal,sf::Vector2u(m_window.getWindow()->getSize().x, 40), m_theme.getColors() ,m_font);

    m_menuBar->addButton("List Mod", [this] {
        JarReader::listJarContents((ResourcePaths::modPath / "create-1.20.1-6.0.6.jar").string());
    });
    m_menuBar->addButton("New Project", [this]{Logger::debug("Created New Project!");});
    m_menuBar->addButton("Open Project", [this] {ProjectFile::load(m_texture);});
    m_menuBar->addButton("Save Project", [this] {ProjectFile::save(m_texture);});
    m_menuBar->addButton("Open Texture", [this] {
        FileDialog::openTexture(m_texture);
        m_sprite->setTexture(m_texture, true);
        centerSprite();
    });
    m_menuBar->addButton("Open Pack", [this] {
        FileDialog::openResourcePack();
    });
    m_menuBar->addButton("Apply Mask", [this] {
        FileDialog::generateMaskFromTexture(m_texture);
        m_sprite->setTexture(m_texture, true);
        centerSprite();
    });



    m_minButton = std::make_unique<OldButton>(ButtonType::Normal,
        sf::Vector2f(0, 0),\
        sf::Vector2f(40, 40), m_font, "Min", m_theme.getColors(), [this]{m_window.minimizeWindow();});

    m_maxButton = std::make_unique<OldButton>(ButtonType::Normal,
        sf::Vector2f(40.f, 0),\
        sf::Vector2f(40, 40), m_font, "Max", m_theme.getColors(), [this]{m_window.maximizeWindow();});

    m_exitButton = std::make_unique<OldButton>(ButtonType::Critical,
        sf::Vector2f(80.f, 0),\
        sf::Vector2f(40, 40), m_font, "Exit", m_theme.getColors(), [this]{m_window.getWindow()->close();});







    m_sprite = std::make_unique<sf::Sprite>(m_texture);

    m_sprite->setScale(spriteScale);
    centerSprite();

    Logger::debug("after scale");
}


void AppUI::centerSprite() const {
    const sf::Vector2f viewSize = m_window.m_mainView->getSize();
    Logger::debug("got size");
    const sf::FloatRect spriteBounds = m_sprite->getGlobalBounds();

    const float posX = (static_cast<float>(viewSize.x) - spriteBounds.size.x) / 2.f;
    const float posY = (static_cast<float>(viewSize.y) - spriteBounds.size.y) / 2.f;

    m_sprite->setPosition(sf::Vector2f(posX, posY));
}
