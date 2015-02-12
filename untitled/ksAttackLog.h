#ifndef KS_ATTACK_LOG_H
#define KS_ATTACK_LOG_H

#include "ksText.h"
#include "ksPlayer.h"
#include "ksAudioTrack.h"
#include <SFML/Graphics.hpp>

enum ksAttackLogTab { ATTACK, DEFEND, ITEM, RUN };

class ksAttackLog : public sf::Drawable, public sf::Transformable
{
	public:
		ksAttackLog();
		~ksAttackLog();

		void setTab( ksAttackLogTab tab );
		void toggle( std::string player_name, int player_hp, int player_max_hp,
					 std::string enemy_name, int enemy_hp, int enemy_max_hp,
					 std::string original_track, std::string battle_track );

		void modPlayerHP( int hp );
		void modEnemyHP( ksPlayer & player, int hp );

		int update( sf::View & map_view, ksAudioTrack & audio, ksPlayer & player, int current_tab, float player_x, float player_y );

		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
		void drawLog( sf::RenderWindow & app );

	private:
		sf::VertexArray m_array;
		std::string m_font_file;

		std::string m_original_track;
		std::string m_battle_track;

		ksText * m_text;
		ksAttackLogTab m_tab;

		int m_current_frame;

		int m_player_hp;
		int m_player_max_hp;

		int m_enemy_hp;
		int m_enemy_max_hp;

		int m_current;
		int m_frame_count;

		bool m_active;
		bool m_toggle;

		float m_coord_x;
		float m_coord_y;
};

#endif