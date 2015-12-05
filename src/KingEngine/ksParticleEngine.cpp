#include "ksParticleEngine.h"
#include <iostream>
#include <time.h>

ksParticleEngine::ksParticleEngine(ksColor color, ksVector location, int size, int num, int speed, int reach)
	: m_color(color), m_size(size),
	m_num(num), m_speed(speed), m_reach(reach)
{
	srand(time(NULL));
	setLayerPosition(location);
}

void ksParticleEngine::update()
{
	for (int count = 0; count < m_num; count++)
		m_particles.push_back(generateParticle());

	for (int particle = 0; particle < m_particles.size(); particle++)
	{
		m_particles[particle].update();

		if (m_particles[particle].m_ttl <= 0)
		{
			m_particles.erase(m_particles.begin() + particle);
			particle--;
		}
	}

	resize(m_particles.size() * 6);

	for (int count = 0; count < m_particles.size(); count++)
	{
		ksVector temp = m_particles[count].m_position;

		addVector2f((count * 6), temp.x, temp.y, m_color);
		addVector2f((count * 6) + 1, temp.x + m_size, temp.y, m_color);
		addVector2f((count * 6) + 2, temp.x + m_size, temp.y + m_size, m_color);
		addVector2f((count * 6) + 3, temp.x, temp.y + m_size, m_color);
		addVector2f((count * 6) + 4, temp.x, temp.y, m_color);
		addVector2f((count * 6) + 5, temp.x + m_size, temp.y + m_size, m_color);
	}
}

ksParticle ksParticleEngine::generateParticle()
{
	return ksParticle(
		getLayerPosition(),
		ksVector(rand() % m_speed + 1, rand() % m_speed + 1),
		rand() % m_reach + 1);
}

void ksParticleEngine::setColor(ksColor color)
{
	m_color = color;
}

void ksParticleEngine::setSize(int size)
{
	m_size = size;
}

void ksParticleEngine::setNumber(int num)
{
	m_num = num;
}

void ksParticleEngine::setVelocity(int vel)
{
	m_speed = vel;
}

void ksParticleEngine::setReach(int reach)
{
	m_reach = reach;
}

ksColor ksParticleEngine::getColor()
{
	return m_color;
}