#ifndef KS_EFFECT_H
#define KS_EFFECT_H

#include "ksTile.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ksEffect : public sf::Drawable, public sf::Transformable
{
	public:
		ksEffect( sf::Color color1, sf::Color color2, 
				  int duration1, int duration2 );

		void set( int light_num, sf::Color color1, sf::Color color2,
				  int duration1, int duration2 );

		void add( sf::Vector2f center, int diameter, sf::Color color1, sf::Color color2 );

		void resizeMap( int width_tiles, int height_tiles );

		void clear();

		void update();
		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;

		sf::Color getFirstColor() { return m_color_1[0]; }
		sf::Color getSecondColor() { return m_color_2[0]; }
		int getFirstDuration() { return m_duration_1; }
		int getSecondDuration() { return m_duration_2; }

	private:
		sf::VertexArray m_array;
		//sf::Color m_color_1;
		//sf::Color m_color_2;

		std::vector<sf::Color> m_color_1;
		std::vector<sf::Color> m_color_2;

		int m_current_color;

		int m_duration_1;
		int m_duration_2;
		int m_current;

		int m_number_of_lights;
};

#endif