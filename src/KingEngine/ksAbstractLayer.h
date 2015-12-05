#ifndef KS_ABSTRACT_LAYER_H
#define KS_ABSTRACT_LAYER_H

#include <iostream>
#include <vector>
#include "ksRenderWindow.h"
#include "ksDrawable.h"
#include "ksAbstract.h"

class ksAbstractLayer : public ksDrawable
{
public:
	ksAbstractLayer(std::string tilesheet);
	void addObject(ksAbstract obj);
	void animate(int object_number, int low, int high, int speed);

	void drawLayer(ksRenderWindow & app);

	ksRect getRect(int object_number) const;
	int getCount();

	void setTileSheet(std::string tilesheet);

	void purge();

private:
	std::vector<ksAbstract> m_abs_array;
	ksRect * m_position;

	int m_num;
};

#endif