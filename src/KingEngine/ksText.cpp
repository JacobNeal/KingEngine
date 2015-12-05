#include "ksText.h"

ksText::ksText()
{ }

ksText::ksText(std::string tilesheet, std::string text, int x, int y, ksColor color, int size)
	: m_string(text), red((int)color.r), green((int)color.g), blue((int)color.b),
	alpha((int)color.a)
{
	setText(tilesheet, text, x, y, color, size);
}

ksText::ksText(const ksText & copy)
	: red((int)copy.red), green((int)copy.green), blue((int)copy.blue),
	alpha((int)copy.alpha)
{
}

ksText & ksText::operator= (const ksText & rhs)
{
	if (this != &rhs)
	{
		m_string = rhs.m_string;

		red = rhs.red;
		green = rhs.green;
		blue = rhs.blue;
		alpha = rhs.alpha;
	}

	return *this;
}


void ksText::setText(std::string tilesheet, std::string text, int x, int y, ksColor color, int size)
{
	m_string = text;
	red = (int)color.r;
	green = (int)color.g;
	blue = (int)color.b;
	alpha = (int)color.a;

	addTexture(tilesheet);
	resize(text.length() * 6);

	int margin = size - (size / 3);

	for (int count = 0; text[count] != '\0'; count++)
	{
		int tile_type = 0;

		if (text[count] >= ' ' && text[count] <= '~')
			tile_type = (text[count] - 32);

		ksRect tsrect((tile_type - (10 * (tile_type / 10))) * 16,
			(tile_type / 10) * 16, 16, 16);

		addVector2f((count * 6), x + (count * margin), y, color);
		addVector2f((count * 6) + 1, x + (count * margin) + size, y, color);
		addVector2f((count * 6) + 2, x + (count * margin) + size, y + size, color);
		addVector2f((count * 6) + 3, x + (count * margin), y + size, color);
		addVector2f((count * 6) + 4, x + (count * margin), y, color);
		addVector2f((count * 6) + 5, x + (count * margin) + size, y + size, color);

		addTextureCoordinates((count * 6), tsrect.x, tsrect.y);
		addTextureCoordinates((count * 6) + 1, tsrect.x + 16, tsrect.y);
		addTextureCoordinates((count * 6) + 2, tsrect.x + 16, tsrect.y + 16);
		addTextureCoordinates((count * 6) + 3, tsrect.x, tsrect.y + 16);
		addTextureCoordinates((count * 6) + 4, tsrect.x, tsrect.y);
		addTextureCoordinates((count * 6) + 5, tsrect.x + 16, tsrect.y + 16);
	}
}

void ksText::setText(ksText & text)
{
	setText("Tiles/consolas_font_map.png", text.m_string, getPosition().x, getPosition().y, ksColor(red, green, blue, alpha));
}

std::string ksText::getText()
{
	return m_string;
}

ksColor ksText::getColor()
{
	return ksColor(red, green, blue, alpha);
}

void ksText::setColor(int red_number, int green_number, int blue_number, int alpha_number)
{
	for (int count = 0; count < m_string.length(); count++)
	{
		setVertexColor(count * 6, ksColor(red_number, green_number, blue_number, alpha_number));
		setVertexColor((count * 6) + 1, ksColor(red_number, green_number, blue_number, alpha_number));
		setVertexColor((count * 6) + 2, ksColor(red_number, green_number, blue_number, alpha_number));
		setVertexColor((count * 6) + 3, ksColor(red_number, green_number, blue_number, alpha_number));
		setVertexColor((count * 6) + 4, ksColor(red_number, green_number, blue_number, alpha_number));
		setVertexColor((count * 6) + 5, ksColor(red_number, green_number, blue_number, alpha_number));
	}
	red = red_number;
	green = green_number;
	blue = blue_number;
	alpha = alpha_number;
}