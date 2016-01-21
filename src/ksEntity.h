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
#include "ksRect.h"
#include "defines.h"

class ksEntity
{
	public:
		//                 Constructors
		ksEntity(ksRect position, int current_tile);
		ksEntity(double x, double y, double w, double h, int current_tile);

		//                 Methods
		virtual void       animate();
		void               move(double x, double y);

		//                 Mutators
		void               setAnimationLower(int lower_tile);
		void               setAnimationUpper(int upper_tile);
		void               setAnimationDelay(int frame_delay);
		void               setPosition(double x, double y);
		void               setPosition(const ksVector2D & position);
		void               setPressed(bool press);
		void               setVisible(bool visible);

		//                 Accessor methods
		const ksVector2D & getPosition();
		const ksRect     & getTextureCoord();
		ksRect             getRect();
		bool               isPressed();
		bool               isVisible();

	private:
		//                 Data members
		ksVector2D         m_position;
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