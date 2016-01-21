/********************************************************
* Class:            ksEntityLayer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntityLayer.h
*
*   Overview:
*       Class that contains a drawable layer of game
*       entities.
*
********************************************************/

#ifndef KS_ENTITY_LAYER_H
#define KS_ENTITY_LAYER_H

#include <SFML/Graphics.hpp>
#include "ksEntity.h"
#include "globals.h"
#include <map>

class ksEntityLayer : public sf::Drawable, public sf::Transformable
{
	public:
		//                      Constructors
		ksEntityLayer(char * tilesheet);
		
		//                      Methods
		void                    addEntity(ksEntity * entity);
        void                    animate(int entity_number, int lower_tile, int upper_tile, int frame_delay);
		bool                    pressEntity(int mouse_x, int mouse_y);
		void                    depressEntity();
		void                    drawLayer(sf::RenderWindow & app);
		virtual void            draw(sf::RenderTarget & target, sf::RenderStates states) const;
		void                    purge();

		//                      Mutators
		bool                    setTilesheet(char * tilesheet);

		//                      Accessor Methods
		ksRect                  getRect(int entity_number);
		int                     getCount();

	private:
		//                      Data members
        sf::VertexArray         m_array;
        std::map<int, ksEntity *> m_entities;
		sf::Texture             m_texture;
        ksRect *                m_position;
		int                     m_num_of_entities;
		ksEntity *              m_pressedEntity;
};

#endif