/********************************************************
* Class:			ksEntity
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntity.h
*
*	Overview:
*		Class for the base game entity in KingEngine.
*
********************************************************/

#ifndef KS_ENTITY_H
#define KS_ENTITY_H

#include "ksVector2D.h"
#include "ksTile.h"
#include "ksRect.h"
#include "ksWorld.h"
#include "ksPathNode.h"
#include "defines.h"
#include <list>
#include <algorithm>

class ksEntity
{
	public:
		//                 Constructors
		ksEntity(ksWorldWall wall, int row, int col, int w, int h, int current_tile);

		//                 Methods
		void               animate();
		virtual void       update();
        //void               move(ksDirection direction);

		//                 Mutators
		void               setAnimationLower(int lower_tile);
		void               setAnimationUpper(int upper_tile);
		void               setAnimationDelay(int frame_delay);
		
        void               setPosition(int row, int col, int depth);
        void               setPressed(bool press);
		void               setVisible(bool visible);

		//                 Accessor methods
		const ksTile &     getTilePosition();
		const ksRect &     getTextureCoord();
		int                getWidth();
        int                getHeight();
        int                getRow();
        int                getColumn();
        ksWorldWall        getWall();
        bool               isPressed();
		bool               isVisible();

	protected:
		//                 Data members
        ksTile             m_position;
        int                m_row;
        int                m_col;
        ksWorldWall        m_wall;
        int                m_width;
        int                m_height;
		ksRect             m_texture_coord;
		int                m_upper_tile;
		int                m_lower_tile;
		int                m_anim_delay;
		int                m_frame;
		int                m_current_tile;
		bool               m_pressed;
		bool               m_visible;
};

#endif
