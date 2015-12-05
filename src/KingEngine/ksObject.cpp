#include "ksObject.h"

ksObject::ksObject(ksRect position, int type)
	: ksAbstract(position, type), m_vel_x(0.f), m_vel_y(0.f)
{ }

/*void ksObject::moveObject(cArray2D<int> objects)
{
m_position.x += m_vel_x;

for (int row = 0; row < objects.getRow(); ++row)
for (int col = 0; col < objects.getColumn(); ++col)
if (objects[row][col] == 1)
if (m_position.checkCollision(ksRect(row * TILE_WIDTH, col * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT)))
m_position.x -= m_vel_x;

m_position.y += m_vel_y;

for (int row = 0; row < objects.getRow(); ++row)
for (int col = 0; col < objects.getColumn(); ++col)
if (objects[row][col] == 1)
if (m_position.checkCollision(ksRect(row * TILE_WIDTH, col * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT)))
m_position.y -= m_vel_y;
}*/

void ksObject::setVelocityX(float velocity)
{
	m_vel_x = velocity;
}

void ksObject::setVelocityY(float velocity)
{
	m_vel_y = velocity;
}

ksRect ksObject::getVelocity() const
{
	return ksRect(m_vel_x, m_vel_y, 0, 0);
}

void ksObject::animate()
{
	ksAbstract::animate();

	/*cArray2D<int> objects(0, 0);

	moveObject(objects);*/
}