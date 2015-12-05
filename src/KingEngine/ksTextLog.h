#ifndef KS_TEXT_LOG_H
#define KS_TEXT_LOG_H

#include "ksRenderWindow.h"
#include "ksText.h"
#include "ksDrawable.h"
#include "ksColor.h"
//#include <SFML/Graphics.hpp>

#define NUM_LINES 7

class ksTextLog : public ksDrawable
{
public:
	ksTextLog(std::string font_file);
	void insert(std::string line, ksColor color = ksColor(255, 255, 255, 255));

	void drawLog(ksRenderWindow & app);

	void update(int frame_time);
	void activate();

	void clear();

	void setLogPosition(float x, float y);
	void moveLog(float x, float y);

private:
	//sf::VertexArray m_array;
	std::string m_font_file;

	ksText m_text_lines[NUM_LINES + 1];

	int m_current;
	int m_frame_count;
	bool m_active;

	float m_coord_x;
	float m_coord_y;
};

#endif