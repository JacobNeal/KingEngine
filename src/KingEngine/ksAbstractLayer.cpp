#include "ksAbstractLayer.h"

ksAbstractLayer::ksAbstractLayer(std::string tilesheet)
	: m_num(0)
{
	addTexture(tilesheet);
}

void ksAbstractLayer::addObject(ksAbstract object)
{
	resize((m_num + 1) * 6);

	m_abs_array.push_back(object);

	ksRect pos = object.getPosition();
	ksRect text = object.getTexture();
	int vec = m_num * 6;

	text.x /= 2;
	text.y /= 2;
	text.w /= 2;
	text.h /= 2;

	addVector2f(vec, pos.x, pos.y);
	addVector2f(vec + 1, pos.x + pos.w, pos.y);
	addVector2f(vec + 2, pos.x + pos.w, pos.y + pos.h);
	addVector2f(vec + 3, pos.x, pos.y + pos.h);
	addVector2f(vec + 4, pos.x, pos.y);
	addVector2f(vec + 5, pos.x + pos.w, pos.y + pos.h);

	addTextureCoordinates(vec, text.x, text.y);
	addTextureCoordinates(vec + 1, text.x + text.w, text.y);
	addTextureCoordinates(vec + 2, text.x + text.w, text.y + text.h);
	addTextureCoordinates(vec + 3, text.x, text.y + text.h);
	addTextureCoordinates(vec + 4, text.x, text.y);
	addTextureCoordinates(vec + 5, text.x + text.w, text.y + text.h);

	m_num++;

	std::cout << "Number of objects: " << m_num << '\n';
}

void ksAbstractLayer::animate(int object_number, int low, int high, int speed)
{
	m_abs_array[object_number].setAnimationLow(low);
	m_abs_array[object_number].setAnimationHigh(high);
	m_abs_array[object_number].setAnimationSpeed(speed);
}

void ksAbstractLayer::drawLayer(ksRenderWindow & app)
{
	for (int count = 0; count < m_num; count++)
	{
		m_abs_array[count].animate();

		ksRect pos = m_abs_array[count].getPosition();
		ksRect text = m_abs_array[count].getTexture();
		int vec = count * 6;

		text.x /= 2;
		text.y /= 2;
		text.w /= 2;
		text.h /= 2;

		addVector2f(vec, pos.x, pos.y);
		addVector2f(vec + 1, pos.x + pos.w, pos.y);
		addVector2f(vec + 2, pos.x + pos.w, pos.y + pos.h);
		addVector2f(vec + 3, pos.x, pos.y + pos.h);
		addVector2f(vec + 4, pos.x, pos.y);
		addVector2f(vec + 5, pos.x + pos.w, pos.y + pos.h);

		addTextureCoordinates(vec, text.x, text.y);
		addTextureCoordinates(vec + 1, text.x + text.w, text.y);
		addTextureCoordinates(vec + 2, text.x + text.w, text.y + text.h);
		addTextureCoordinates(vec + 3, text.x, text.y + text.h);
		addTextureCoordinates(vec + 4, text.x, text.y);
		addTextureCoordinates(vec + 5, text.x + text.w, text.y + text.h);
	}

	app.drawObject(this);
}

ksRect ksAbstractLayer::getRect(int object_number) const
{
	return m_abs_array[object_number].getPosition();
}

void ksAbstractLayer::setTileSheet(std::string tilesheet)
{
	addTexture(tilesheet);
}

int ksAbstractLayer::getCount()
{
	return m_num;
}

void ksAbstractLayer::purge()
{
	m_array.clear();
	m_abs_array.clear();
	m_num = 0;
}