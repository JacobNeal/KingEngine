/************************************************************
* Class: ksTile
*
* Constructors:
*		ksTile( int x, int y, int type )
*				Initialize the x and y coordinates and type
*				of tile to the passed values.
*		ksTile( const ksTile & copy )
*				Initialize the tile to the passed value.
*
* Methods:
*		ksTile & operator= ( const ksTile & rhs )
*				Set the tile to the passed value.
*		void show( sf::RenderWindow * app, sf::Texture & text, 
				   ksRect & camera )
*				Set up the tile to the correct texture rect
*				and position then draw to screen.
*		int getType()
*				Return the type of tile.
************************************************************/

#ifndef KS_TILE_H
#define KS_TILE_H

#include <SFML/Graphics.hpp>
#include "ksRect.h"

// Regular Window Size 800 x 640
// HD Window Size 1280 x 960

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

#define MAP_WIDTH 1600
#define MAP_HEIGHT 1280

// MAP SIZE
// TOTAL TILES 2000
// 1600 x 1280

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define TOTAL_TILES 2000
#define TILE_SPRITES 64
#define TILE_PER_LINE 9

#endif