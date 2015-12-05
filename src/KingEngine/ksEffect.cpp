#include "ksEffect.h"

ksEffect::ksEffect(ksColor color1, ksColor color2,
	int duration1, int duration2)
	: m_current_color(1),
	m_duration_1(duration1),
	m_duration_2(duration2),
	m_number_of_lights(1),
	m_current(0)
{
	setPrimitiveType("triangle");
	resize(24);

	m_color_1.push_back(color1);
	m_color_2.push_back(color2);

	// Edge = 400
	// Radius = 540

	// Center
	addVector2f(0, 400, 320, color1);
	addVector2f(1, 800, -80, color1);
	addVector2f(2, 940, 320, color1);

	addVector2f(3, 400, 320, color1);
	addVector2f(4, 940, 320, color1);
	addVector2f(5, 800, 720, color1);

	addVector2f(6, 400, 320, color1);
	addVector2f(7, 800, 720, color1);
	addVector2f(8, 400, 860, color1);

	addVector2f(9, 400, 320, color1);
	addVector2f(10, 400, 860, color1);
	addVector2f(11, 0, 720, color1);

	addVector2f(12, 400, 320, color1);
	addVector2f(13, 0, 720, color1);
	addVector2f(14, -140, 320, color1);

	addVector2f(15, 400, 320, color1);
	addVector2f(16, -140, 320, color1);
	addVector2f(17, 0, -80, color1);

	addVector2f(18, 400, 320, color1);
	addVector2f(19, 0, -80, color1);
	addVector2f(20, 400, -220, color1);

	addVector2f(21, 400, 320, color1);
	addVector2f(22, 400, -220, color1);
	addVector2f(23, 800, -80, color1);
}

void ksEffect::set(int light_num, ksColor color1, ksColor color2,
	int duration1, int duration2)
{
	//clear();

	m_color_1[light_num] = color1;
	m_color_2[light_num] = color2;
	m_current_color = 1;
	m_duration_1 = duration1;
	m_duration_2 = duration2;
	m_current = 0;
}

void ksEffect::add(int center_x, int center_y, int diameter, ksColor color1, ksColor color2)
{
	int radius = diameter / 2;
	int edge = (3 * radius) / 4;
	int temp_vertex = m_number_of_lights * 24;

	resize((m_number_of_lights + 1) * 24);

	addVector2f(temp_vertex, center_x, center_y);
	addVector2f(temp_vertex + 1, center_x + edge, center_y - edge);
	addVector2f(temp_vertex + 2, center_x + radius, center_y);

	addVector2f(temp_vertex + 3, center_x, center_y);
	addVector2f(temp_vertex + 4, center_x + radius, center_y);
	addVector2f(temp_vertex + 5, center_x + edge, center_y + edge);

	addVector2f(temp_vertex + 6, center_x, center_y);
	addVector2f(temp_vertex + 7, center_x + edge, center_y + edge);
	addVector2f(temp_vertex + 8, center_x, center_y + radius);

	addVector2f(temp_vertex + 9, center_x, center_y);
	addVector2f(temp_vertex + 10, center_x, center_y + radius);
	addVector2f(temp_vertex + 11, center_x - edge, center_y + edge);

	addVector2f(temp_vertex + 12, center_x, center_y);
	addVector2f(temp_vertex + 13, center_x - edge, center_y + edge);
	addVector2f(temp_vertex + 14, center_x - radius, center_y);

	addVector2f(temp_vertex + 15, center_x, center_y);
	addVector2f(temp_vertex + 16, center_x - radius, center_y);
	addVector2f(temp_vertex + 17, center_x - edge, center_y - edge);

	addVector2f(temp_vertex + 18, center_x, center_y);
	addVector2f(temp_vertex + 19, center_x - edge, center_y - edge);
	addVector2f(temp_vertex + 20, center_x, center_y - radius);

	addVector2f(temp_vertex + 21, center_x, center_y);
	addVector2f(temp_vertex + 22, center_x, center_y - radius);
	addVector2f(temp_vertex + 23, center_x + edge, center_y - edge);

	m_color_1.push_back(color1);
	m_color_2.push_back(color2);

	m_number_of_lights++;
}

void ksEffect::resizeMap(int width_tiles, int height_tiles)
{
	int x = width_tiles * TILE_WIDTH;
	int y = height_tiles * TILE_WIDTH;

	int diameter = 1.35 * x;
	int radius = diameter / 2;
	int edge = (3 * radius) / 4;

	int center_x = (x / 2);
	int center_y = (y / 2);

	addVector2f(0, center_x, center_y);
	addVector2f(1, center_x + edge, center_y - edge);
	addVector2f(2, center_x + radius, center_y);

	addVector2f(3, center_x, center_y);
	addVector2f(4, center_x + radius, center_y);
	addVector2f(5, center_x + edge, center_y + edge);

	addVector2f(6, center_x, center_y);
	addVector2f(7, center_x + edge, center_y + edge);
	addVector2f(8, center_x, center_y + radius);

	addVector2f(9, center_x, center_y);
	addVector2f(10, center_x, center_y + radius);
	addVector2f(11, center_x - edge, center_y + edge);

	addVector2f(12, center_x, center_y);
	addVector2f(13, center_x - edge, center_y + edge);
	addVector2f(14, center_x - radius, center_y);

	addVector2f(15, center_x, center_y);
	addVector2f(16, center_x - radius, center_y);
	addVector2f(17, center_x - edge, center_y - edge);

	addVector2f(18, center_x, center_y);
	addVector2f(19, center_x - edge, center_y - edge);
	addVector2f(20, center_x, center_y - radius);

	addVector2f(21, center_x, center_y);
	addVector2f(22, center_x, center_y - radius);
	addVector2f(23, center_x + edge, center_y - edge);
}

void ksEffect::update()
{
	if (m_current < m_duration_1)
		m_current++;
	else if (m_current >= m_duration_1 && m_current - m_duration_1 < m_duration_2)
	{
		m_current_color = 2;
		m_current++;
	}
	else
	{
		m_current = 0;
		m_current_color = 1;
	}

	for (int count = 0; count < 24; count++)
	{
		ksColor inner_color;
		ksColor outer_color;

		if (m_current_color == 1)
			inner_color = m_color_1[0];
		else
			inner_color = m_color_2[0];

		outer_color = inner_color;
		outer_color.a -= inner_color.a / 2;

		if (count % 3 == 0)
			m_array[count].color = outer_color;
		else
			m_array[count].color = inner_color;
	}

	for (int count = 1; count < m_number_of_lights; count++)
	{
		int vertex_temp = count * 24;
		ksColor inner_color;
		ksColor outer_color;

		if (m_current_color == 1)
			inner_color = m_color_1[count];
		else
			inner_color = m_color_2[count];

		outer_color = inner_color;
		outer_color.a -= (3 * outer_color.a) / 4;

		m_array[vertex_temp].color = inner_color;

		for (int current_vertex = 1; current_vertex < 24; current_vertex++)
		{
			if (current_vertex % 3 == 0)
				m_array[vertex_temp + current_vertex].color = inner_color;
			else
				m_array[vertex_temp + current_vertex].color = outer_color;
		}
	}
}

void ksEffect::clear()
{
	clearLayer();
	m_color_1.clear();
	m_color_2.clear();

	m_number_of_lights = 1;
	m_array.resize(24);

	m_color_1.push_back(ksColor(0, 0, 0, 0));
	m_color_2.push_back(ksColor(0, 0, 0, 0));

	addVector2f(0, 400, 320);
	addVector2f(1, 800, -80);
	addVector2f(2, 940, 320);

	addVector2f(3, 400, 320);
	addVector2f(4, 940, 320);
	addVector2f(5, 800, 720);

	addVector2f(6, 400, 320);
	addVector2f(7, 800, 720);
	addVector2f(8, 400, 860);

	addVector2f(9, 400, 320);
	addVector2f(10, 400, 860);
	addVector2f(11, 0, 720);

	addVector2f(12, 400, 320);
	addVector2f(13, 0, 720);
	addVector2f(14, -140, 320);

	addVector2f(15, 400, 320);
	addVector2f(16, -140, 320);
	addVector2f(17, 0, -80);

	addVector2f(18, 400, 320);
	addVector2f(19, 0, -80);
	addVector2f(20, 400, -220);

	addVector2f(21, 400, 320);
	addVector2f(22, 400, -220);
	addVector2f(23, 800, -80);
}