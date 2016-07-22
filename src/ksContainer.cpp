////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksContainer.h"
#include <math.h>

#define PI 3.14

////////////////////////////////////////////////////////////
ksContainer::ksContainer(double width, double height, ksAlign alignment, 
    ksColor color, double radius, int resolution)
    : m_alignment(alignment), m_width(width), m_height(height),
    m_pressed(false), m_color(color), m_radius(radius), m_resolution(resolution),
    m_visible(true), m_opacity(1.0)
{   
    m_array.setPrimitiveType(sf::Triangles);
    
    // Calculate the vertices to draw the container.
    update();
}

////////////////////////////////////////////////////////////
void ksContainer::addControl(ksControl * control)
{
    m_controls.push_back(control);
    
    // Update the contained controls
    updateContainedControls();
}

////////////////////////////////////////////////////////////
bool ksContainer::getVisibility()
{
    return m_visible;
}

////////////////////////////////////////////////////////////
void ksContainer::update()
{
    // Number of sides that make up a corner times 4 corners
    // plus 4 sides.
    int number_of_triangles = (m_resolution * 4) + 4;
    
    // Number of triangles * 3 vertices per triangle
    m_array.clear();
    m_array.resize(number_of_triangles * 3);
    
    // Total vertices = 1 center + ((resolution + 1) * 4)
    int total_vertices = 1 + ((m_resolution + 1) * 4);
    sf::Vector2f * vertices = new sf::Vector2f [total_vertices];
    
    // Center
    vertices[0].x = m_width / 2;
    vertices[0].y = m_height / 2;
    
    float angle = 270.0f;
    int vertex_array_count = 0;
    
    // If the radius is larger than half the height or width then cap it.
    if (m_radius > (m_width * 0.5))
        m_radius = m_width * 0.5;
    if (m_radius > (m_height * 0.5))
        m_radius = m_height * 0.5;
    
    // Working from the inner to the outter.
    for (int count = 0; count < m_resolution + 1; ++count)
    {
        float anglerad = (PI * angle) / 180.0f;
        
        // Top Left
        vertices[1 + count].x = (sinf(anglerad) * m_radius) + m_radius;
        vertices[1 + count].y = (cosf(anglerad) * m_radius) + m_radius;
        
        // Top Right
        vertices[2 + m_resolution + count].x = (m_width - (m_radius * 2)) + (m_radius - (vertices[1 + count].x)) + m_radius;
        vertices[2 + m_resolution + count].y = vertices[1 + count].y;
        
        // Bottom Right
        vertices[3 + (m_resolution * 2) + count].x = vertices[2 + m_resolution + count].x;
        vertices[3 + (m_resolution * 2) + count].y = (m_height - (m_radius * 2)) + (m_radius - (vertices[1 + count].y)) + m_radius;
        
        // Bottom Left
        vertices[4 + (m_resolution * 3) + count].x = vertices[1 + count].x;
        vertices[4 + (m_resolution * 3) + count].y = vertices[3 + (m_resolution * 2) + count].y;
        
        // 90 degress for top left corner divided by
        // the number of sides that make up the corner.
        angle -= (float) 90 / m_resolution;
    }
    
    for (int count = 2; count < total_vertices; ++count)
    {
        if ((count - 1) == ((m_resolution + 1) * 2))
        {
            m_array[vertex_array_count++] = sf::Vertex(vertices[0], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[m_resolution + 2], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count], m_color);
        }
        else if ((count - 1) % (m_resolution + 1) == 0)
        {
            m_array[vertex_array_count++] = sf::Vertex(vertices[0], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count - 1], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count + m_resolution], m_color);
        }
        else if (count == total_vertices - 1)
        {
            // Insert the final triangle for the bottom right corner.
            m_array[vertex_array_count++] = sf::Vertex(vertices[0], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count - 1], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count], m_color);
            
            // Insert the final side of the container.
            m_array[vertex_array_count++] = sf::Vertex(vertices[0], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[1], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[1 + ((m_resolution + 1) * 3)], m_color);
        }
        else
        {
            m_array[vertex_array_count++] = sf::Vertex(vertices[0], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count - 1], m_color);
            m_array[vertex_array_count++] = sf::Vertex(vertices[count], m_color);
        }
    }
    
    delete [] vertices;
    
    // Update the contained controls
    updateContainedControls();
}

////////////////////////////////////////////////////////////
void ksContainer::updateContainedControls()
{
    double current_x = 0.0;
    double current_y = 0.0;
    
    switch (m_alignment)
    {
        case ksAlign::CENTER:
            current_x = (double) getPosition().x + (m_width / 2);
            current_y = (double) getPosition().y + (m_height / 2);
            break;
            
        case ksAlign::COLUMN:
            current_x = (double) getPosition().x + (m_width / 2);
            current_y = (double) getPosition().y + (m_height / m_controls.size()) / 2;
            break;
            
        case ksAlign::ROW:
            current_x = (double) getPosition().x + (m_width / m_controls.size()) / 2;
            current_y = (double) getPosition().y + (m_height / 2);
            break;
            
        default:
            current_x = (double) getPosition().x + (m_width / 2);
            current_y = (double) getPosition().y + (m_height / 2);
    }
    
    // Update the contained controls
    for (int count = 0; count < m_controls.size(); ++count)
    {
        m_controls[count]->setCenter(current_x, current_y);
        
        if (m_alignment == ksAlign::COLUMN)
            current_y += (double) (m_height / m_controls.size());
        else if (m_alignment == ksAlign::ROW)
            current_x += (double) (m_width / m_controls.size());
    }
}

////////////////////////////////////////////////////////////
void ksContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

////////////////////////////////////////////////////////////
void ksContainer::drawControl(sf::RenderWindow & app)
{
    if (m_visible)
    {
        // Draw the rounded rectangle of the container.
        app.draw(*this);
        
        // Draw all the nested controls within the container.
        for (int count = 0; count < m_controls.size(); ++count)
            m_controls[count]->drawControl(app);
    }
}

////////////////////////////////////////////////////////////
void ksContainer::moveControl(double x, double y)
{
    move(x, y);
    
    // Update the position of all nested controls in
    // the container.
    for (int count = 0; count < m_controls.size(); ++count)
        m_controls[count]->moveControl(x, y);
}

////////////////////////////////////////////////////////////
bool ksContainer::pressed(int mouse_x, int mouse_y)
{   
    bool contained_control_pressed = false;
    
    // Check to see if any contained controls are pressed.
    for (int count = 0; count < m_controls.size(); ++count)
    {
        if (m_controls[count]->pressed(mouse_x, mouse_y))
        {
            contained_control_pressed = true;
            m_pressed = true;
            break;
        }
    }
    
    if (!contained_control_pressed &&
        mouse_x >= getPosition().x &&
        mouse_x <= getPosition().x + m_width &&
        mouse_y >= getPosition().y &&
        mouse_y <= getPosition().y + m_height)
    {
        m_pressed = true;
    }
    
    return m_pressed;
}

////////////////////////////////////////////////////////////
bool ksContainer::isPressed()
{
    return m_pressed;
}

////////////////////////////////////////////////////////////
void ksContainer::resize(int screen_width, int screen_height)
{
    // Update the size of the control.
    m_width = (double) (m_width / DEFAULT_WINDOW_WIDTH) * screen_width;
    m_height = (double) (m_height / DEFAULT_WINDOW_HEIGHT) * screen_height;
    
    // Update the position of the control
    setPosition((getPosition().x / DEFAULT_WINDOW_WIDTH) * screen_width,
                (getPosition().y / DEFAULT_WINDOW_HEIGHT) * screen_height);
                
    // Call the resize method of all contained controls.
    for (int count = 0; count < m_controls.size(); ++count)
        m_controls[count]->resize(screen_width, screen_height);
    
    // Update the size and position of the container.
    update();
}

////////////////////////////////////////////////////////////
void ksContainer::setCenter(double x, double y)
{
    setPosition(x - (m_width / 2), y - (m_height / 2));
    
    // Update the position of the contained controls.
    updateContainedControls();
}

////////////////////////////////////////////////////////////
void ksContainer::setColor(ksColor color)
{
    m_color = color;
    
    // Update the color of the container.
    for (int count = 0; count < m_array.getVertexCount(); ++count)
        m_array[count].color = m_color;
}

////////////////////////////////////////////////////////////
void ksContainer::setControlPosition(double x, double y)
{
    setPosition(x, y);
    
    // Update the contained controls
    updateContainedControls();
}

////////////////////////////////////////////////////////////
void ksContainer::setOpacity(double opacity)
{
    // Take the value of opacity from 0.0 - 1.0
    // to either be completely translucent or visible
    // and update the alpha of the container color.
    m_color.a = opacity * 255;
    
    // Update the opacity of all contained controls.
    for (int count = 0; count < m_controls.size(); ++count)
        m_controls[count]->setOpacity(opacity);
        
    m_opacity = opacity;
    
    // Update the container.
    update();
}

////////////////////////////////////////////////////////////
void ksContainer::setPressed(bool pressed)
{
    m_pressed = pressed;
}

////////////////////////////////////////////////////////////
void ksContainer::setWidth(double width)
{
    m_width = width;
    
    // Update the container and all the contained controls.
    update();
}

////////////////////////////////////////////////////////////
void ksContainer::setHeight(double height)
{
    m_height = height;
    
    // Update the container and all the contained controls.
    update();
}

////////////////////////////////////////////////////////////
void ksContainer::setVisibility(bool visibility)
{
    m_visible = visibility;
}