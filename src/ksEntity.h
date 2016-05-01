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
		ksEntity(ksWorld * world, int x, int y, int z, int w, int h, int current_tile);

		//                 Methods
		void               animate();
		virtual void       update();
        //void               move(ksDirection direction);

		//                 Mutators
		void               setAnimationLower(int lower_tile);
		void               setAnimationUpper(int upper_tile);
		void               setAnimationDelay(int frame_delay);
        void               setPressed(bool press);
		void               setVisible(bool visible);
        void               setTilePosition(ksPathNode node);

		//                 Accessor methods
		const ksPathNode & getTilePosition();
		const ksRect &     getTextureCoord();
		int                getWidth();
        int                getHeight();
        bool               isPressed();
		bool               isVisible();
        int                X();
        int                Y();
        int                Z();

	protected:
		//                 Data members
        ksWorld *          m_world;
        ksPathNode         m_current_node;
        int                m_width;
        int                m_height;
		int                m_current_tile;
		ksRect             m_texture_coord;
		int                m_upper_tile;
		int                m_lower_tile;
		int                m_anim_delay;
		int                m_frame;
		bool               m_pressed;
		bool               m_visible;
        int                m_x;
        int                m_y;
        int                m_z;
        int                m_w;
        int                m_h;
};

#endif
