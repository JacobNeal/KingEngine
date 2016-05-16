/********************************************************
* Class:            ksContainer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksContainer.cpp
********************************************************/

#include "ksContainer.h"
#include <math.h>

#define PI 3.14

/********************************************************
*   ksContainer
*
*   Initializes the ksContainer class to a particular
*   alignment that controls within this container will
*   be dynamically updated to when the width, height,
*   or x, y position of the container changes.
********************************************************/
ksContainer::ksContainer(double width, double height, ksAlign alignment, 
    ksColor color, double radius, int resolution)
    : m_alignment(alignment), m_width(width), m_height(height),
    m_pressed(false), m_color(color), m_radius(radius), m_resolution(resolution),
    m_visible(true)
{   
    m_array.setPrimitiveType(sf::Triangles);
    
    // Calculate the vertices to draw the container.
    update();
}

/********************************************************
*   addControl
*
*   Add a control to the list of controls contained within
*   the container.
********************************************************/
void ksContainer::addControl(ksControl * control)
{
    m_controls.push_back(control);
    
    // Update the contained controls
    updateContainedControls();
}

/********************************************************
*   getVisibility
*
*   Return the visibility of the control.
********************************************************/
bool ksContainer::getVisibility()
{
    return m_visible;
}

/********************************************************
*   update
*
*   Updates the current state of the container.
********************************************************/
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

/********************************************************
*   updateContainedControls
*
*   Updates the position of the controls contained within
*   the container.
********************************************************/
void ksContainer::updateContainedControls()
{
    double current_x = 0.0;
    double current_y = 0.0;
    
    if (m_alignment == ksAlign::CENTER)
    {
        current_x = (double) getPosition().x + (m_width / 2);
        current_y = (double) getPosition().y + (m_height / 2);
    }
    else if (m_alignment == ksAlign::COLUMN)
    {
        current_x = (double) getPosition().x + (m_width / 2);
        current_y = (double) getPosition().y + (m_height / m_controls.size()) / 2;
    }
    else if (m_alignment == ksAlign::ROW)
    {
        current_x = (double) getPosition().x + (m_width / m_controls.size()) / 2;
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

/********************************************************
*   draw
*
*   Override the default behavior for drawing objects
*   in SFML.
********************************************************/
void ksContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

/********************************************************
*   drawControl
*
*   Draws the control along with any other associated
*   object to the screen.
********************************************************/
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

/********************************************************
*   moveControl
*
*   Move the container and any associated controls within
*   the container by the passed (x, y) values.
********************************************************/
void ksContainer::moveControl(double x, double y)
{
    move(x, y);
    
    // Update the position of all nested controls in
    // the container.
    for (int count = 0; count < m_controls.size(); ++count)
        m_controls[count]->moveControl(x, y);
}

/********************************************************
*   pressed
*
*   Return whether or not the control is pressed within
*   the passed coordinates.
********************************************************/
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

/********************************************************
*   isPressed
*
*   Return whether or not the control is already pressed.
********************************************************/
bool ksContainer::isPressed()
{
    return m_pressed;
}

/********************************************************
*   resize
*
*   Resize the container based on the new application
*   width and height.
********************************************************/
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

/********************************************************
*   setCenter
*
*   Position the control relative to the passed (x, y)
*   pair that represents the future center position.
********************************************************/
void ksContainer::setCenter(double x, double y)
{
    setPosition(x - (m_width / 2), y - (m_height / 2));
    
    // Update the position of the contained controls.
    updateContainedControls();
}

/********************************************************
*   setColor
*
*   Set the color of the rounded rectangle of the
*   container.
********************************************************/
void ksContainer::setColor(ksColor color)
{
    m_color = color;
    
    // Update the color of the container.
    for (int count = 0; count < m_array.getVertexCount(); ++count)
        m_array[count].color = m_color;
}

/********************************************************
*   setControlPosition
*
*   Position the control relative to the passed (x, y)
*   pair.
********************************************************/
void ksContainer::setControlPosition(double x, double y)
{
    setPosition(x, y);
    
    // Update the contained controls
    updateContainedControls();
}

/********************************************************
*   setPressed
*
*   Set whether or not the control is pressed.
********************************************************/
void ksContainer::setPressed(bool pressed)
{
    m_pressed = pressed;
}

/********************************************************
*   setWidth
*
*   Set the width of the container and dynamically update
*   the position of all the contained controls.
********************************************************/
void ksContainer::setWidth(double width)
{
    m_width = width;
    
    // Update the container and all the contained controls.
    update();
}

/********************************************************
*   setHeight
*
*   Set the height of the container and dynamically update
*   the position of all the contained controls.
********************************************************/
void ksContainer::setHeight(double height)
{
    m_height = height;
    
    // Update the container and all the contained controls.
    update();
}

/********************************************************
*   setVisibility
*
*   Set the visibility of the control.
********************************************************/
void ksContainer::setVisibility(bool visibility)
{
    m_visible = visibility;
}