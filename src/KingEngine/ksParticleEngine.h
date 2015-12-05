#ifndef KS_PARTICLE_ENGINE_H
#define KS_PARTICLE_ENGINE_H

#include <vector>
#include "ksDrawable.h"
#include "ksColor.h"
#include "ksVector.h"
#include "ksParticle.h"

class ksParticleEngine : public ksDrawable
{
public:
	ksParticleEngine(ksColor color, ksVector location, int size = 8, int num = 10, int speed = 20, int reach = 20);
	void update();

	void setColor(ksColor color);
	void setSize(int size);
	void setNumber(int num);
	void setVelocity(int vel);
	void setReach(int reach);

	ksColor getColor();

private:
	ksParticle generateParticle();
	ksColor m_color;

	int m_size;
	int m_num;
	int m_speed;
	int m_reach;

	std::vector<ksParticle> m_particles;
};

#endif