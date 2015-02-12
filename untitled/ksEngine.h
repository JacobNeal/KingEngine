#ifndef KS_ENGINE_H
#define KS_ENGINE_H

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "ksMap.h"
#include "ksAbstractLayer.h"
#include "ksPlayer.h"
#include "ksTextLog.h"
#include "ksMenu.h"
#include "ksParticleEngine.h"
#include "ksEffect.h"
#include "ksAudioTrack.h"
#include "ksAttackLog.h"

enum GameMode { PLAYER_ACTIVE, MENU_ACTIVE, BATTLE_ACTIVE, DIALOG_ACTIVE };

class ksEngine
{
	public:
		ksEngine( char * mapfile, char * objfile, char * playerfile );
		ksEngine();
		void Play();
		void setLUA( lua_State *& luastate );

		void setScript( std::string filename );
		void loadScript();
		void runScript( std::string filename );

		void boundCamera();
		void activateDialog( std::string text, sf::Color color, sf::Vector2f center );

	private:
		void drawEngine();

		// Window
		sf::RenderWindow m_app;

		// Views
		sf::View m_map_view;
		sf::View m_menu_view;
		sf::View m_dialog_view;

		bool m_dialog_active;

		// Background Map and Object Layer
		ksMap m_map;
		ksAbstractLayer m_layer;

		ksMenu m_menu;
		
		ksParticleEngine m_particles;
		ksParticleEngine m_foreground_particles;

		ksText m_fps_count;

		ksEffect m_foreground_effect;

		ksAudioTrack m_back_track;

		ksPlayer m_player;
		ksTextLog m_text_log;
		ksAttackLog m_attack_log;

		int m_map_switch_count;
		bool m_map_switch;
		std::string m_map_switch_file;

		lua_State * m_lua;

		GameMode m_logic;
};

#endif