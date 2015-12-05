#ifndef KS_EFFECT_H
#define KS_EFFECT_H

#include "ksTile.h"
#include "ksDrawable.h"
#include <vector>

class ksEffect : public ksDrawable
{
public:
	ksEffect(ksColor color1, ksColor color2,
		int duration1, int duration2);

	void set(int light_num, ksColor color1, ksColor color2,
		int duration1, int duration2);

	// Add a lighting effect to the layer.
	void add(int center_x, int center_y, int diameter, ksColor color1, ksColor color2);

	void resizeMap(int width_tiles, int height_tiles);

	void clear();
	void update();

	// Getter Methods
	sf::Color	getFirstColor()			{ return m_color_1[0]; }
	sf::Color	getSecondColor()		{ return m_color_2[0]; }
	int			getFirstDuration()		{ return m_duration_1; }
	int			getSecondDuration()		{ return m_duration_2; }

private:
	std::vector<ksColor> m_color_1;
	std::vector<ksColor> m_color_2;

	int m_current_color;

	int m_duration_1;
	int m_duration_2;
	int m_current;

	int m_number_of_lights;
};

#endif