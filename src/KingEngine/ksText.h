#ifndef KS_TEXT_H
#define KS_TEXT_H

#include "ksDrawable.h"
#include "ksColor.h"
#include "ksRect.h"

class ksText : public ksDrawable
{
public:
	ksText();
	ksText(std::string tilesheet, std::string text, int x, int y, ksColor color = ksColor(255, 255, 255, 255), int size = 16);
	ksText(const ksText & copy);
	ksText & operator= (const ksText & rhs);

	void setText(std::string tilesheet, std::string text, int x, int y, ksColor color = ksColor(255, 255, 255, 255), int size = 16);
	void setText(ksText & text);
	std::string getText();
	ksColor getColor();

	void setColor(int red_number, int green_number, int blue_number, int alpha_number = 255);

	int red;
	int green;
	int blue;
	int alpha;

private:
	std::string m_string;
};

#endif