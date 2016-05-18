/********************************************************
* Class:            ksImageControl
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksImageControl.cpp
********************************************************/

#include "ksImageControl.h"
#include <iostream>

ksImageControl::ksImageControl(std::string tilesheet, double x, double y, int width, int height)
    : m_visible(true), m_pressed(false)
{
    if (!m_texture.loadFromFile(tilesheet))
        std::cout << "ERROR (ksImageControl): Couldn't load texture.\n";
        
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
   
    m_sprite.setPosition(x, y);
}

void ksImageControl::drawControl(sf::RenderWindow & app)
{
    if (m_visible)
        app.draw(m_sprite);
}

bool ksImageControl::getVisibility()
{
    return m_visible;
}

void ksImageControl::moveControl(double x, double y)
{
    m_sprite.move(x, y);
}

bool ksImageControl::pressed(int mouse_x, int mouse_y)
{
    if (m_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
        m_pressed = true;
    else
        m_pressed = false;
        
    return m_pressed;
}

bool ksImageControl::isPressed()
{
    return m_pressed;
}

void ksImageControl::resize(int screen_width, int screen_height)
{
    //Nothing to do.
}

void ksImageControl::setCenter(double x, double y)
{
    m_sprite.setPosition(x - (m_sprite.getTextureRect().width / 2),
                         y - (m_sprite.getTextureRect().height / 2));
}

void ksImageControl::setControlPosition(double x, double y)
{
    m_sprite.setPosition(x, y);
}

void ksImageControl::setOpacity(double opacity)
{
    m_sprite.setColor(sf::Color(255, 255, 255, opacity * 255));
}

void ksImageControl::setPressed(bool pressed)
{
    m_pressed = pressed;
}

void ksImageControl::setVisibility(bool visibility)
{
    m_visible = visibility;
}