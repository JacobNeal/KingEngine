#ifndef KS_ABSTRACT_H
#define KS_ABSTRACT_H

#include "ksRect.h"

const int TILES_PER_LINE = 9;

class ksAbstract
{
public:
	ksAbstract(ksRect position, int type);
	virtual void animate();
	ksRect getPosition() const;
	ksRect getTexture() const;

	void setAnimationLow(int low);
	void setAnimationHigh(int high);
	void setAnimationSpeed(int speed);

protected:
	ksRect m_position;
	ksRect m_texture;

	int m_high;
	int m_low;
	int m_speed;

	int m_frame;
	int m_type;
};

#endif