/************************************************************
* Author:					Jacob Neal
* Date Created:				5/28/14
* Last Modification Date:	2/11/15
* Project:					KingEngine v0.1 Alpha
* Filename:					driver.cpp
*
* Overview:
*	The purpose of this project is to create a graphical
*	2D game engine that renders in a top down perspective.
*	This engine will be complete with a
*		-basic particle engine
*		-foreground effects for a weather system
*		-path finding for enemies and NPCs
*		-customizable battle system
*		-audio engine for a background track and additional
*			sound effects.
*
* Input:
*	Key inputs for moving the character (W, A, S, D)
*	Opening the menu system (L Key)
*	Starting a demo battle system (Work in progress) (K Key)
*	To close text windows / prompts (Enter Key)
************************************************************/

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <iostream>
#include "ksEngine.h"

int main()
{
	// Memory Leak Checker
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	ksEngine game;

	game.Play();

	return 0;
}