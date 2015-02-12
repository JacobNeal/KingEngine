#include "ksAttackLog.h"

#define FADE_OUT_FRAME_COUNT 30
#define FADE_IN_FRAME_COUNT 60

ksAttackLog::ksAttackLog()
	: m_tab( ATTACK ), m_current( 0 ), m_active( false ), m_toggle( false ), m_current_frame( 0 )
{
	m_text = new ksText[ 8 ];

	m_text[ 0 ].setText( "Tiles/consolas_font_map.png", "Attack", 0, 512 );
	m_text[ 1 ].setText( "Tiles/consolas_font_map.png", "Defend", 168, 512 );
	m_text[ 2 ].setText( "Tiles/consolas_font_map.png", "Item", 0, 576 );
	m_text[ 3 ].setText( "Tiles/consolas_font_map.png", "Run", 168, 576 );

	m_text[ 4 ].setText( "Tiles/consolas_font_map.png", "Blacksmith", 800 - ( strlen( "Blacksmith" ) * 24 ), 544, sf::Color( 200, 0, 0, 255 ), 32 );
	m_text[ 5 ].setText( "Tiles/consolas_font_map.png", "Enemy", 24, 0, sf::Color( 200, 0, 0, 255 ), 32 );

	m_text[ 6 ].setText( "Tiles/consolas_font_map.png", "20/20", 564, 576, sf::Color( 200, 0, 0, 200 ), 64 );
	m_text[ 7 ].setText( "Tiles/consolas_font_map.png", "20/20", 0, 32, sf::Color( 200, 0, 0, 200 ), 64 );

	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( 20 );

	m_array[ 0 ].position = sf::Vector2f( 0, 512 );
	m_array[ 1 ].position = sf::Vector2f( 168, 512 );
	m_array[ 2 ].position = sf::Vector2f( 168, 576 );
	m_array[ 3 ].position = sf::Vector2f( 0, 576 );

	m_array[ 4 ].position = sf::Vector2f( 168, 512 );
	m_array[ 5 ].position = sf::Vector2f( 336, 512 );
	m_array[ 6 ].position = sf::Vector2f( 336, 576 );
	m_array[ 7 ].position = sf::Vector2f( 168, 576 );

	m_array[ 8 ].position = sf::Vector2f( 0, 576 );
	m_array[ 9 ].position = sf::Vector2f( 168, 576 );
	m_array[ 10 ].position = sf::Vector2f( 168, 640 );
	m_array[ 11 ].position = sf::Vector2f( 0, 640 );

	m_array[ 12 ].position = sf::Vector2f( 168, 576 );
	m_array[ 13 ].position = sf::Vector2f( 336, 576 );
	m_array[ 14 ].position = sf::Vector2f( 336, 640 );
	m_array[ 15 ].position = sf::Vector2f( 168, 640 );

	m_array[ 16 ].position = sf::Vector2f( 0.f, 0.f );
	m_array[ 17 ].position = sf::Vector2f( 800.f, 0.f );
	m_array[ 18 ].position = sf::Vector2f( 800.f, 640.f );
	m_array[ 19 ].position = sf::Vector2f( 0.f, 640.f );

	m_array[ 16 ].color = sf::Color( 0, 0, 0, 0 );
	m_array[ 17 ].color = sf::Color( 0, 0, 0, 0 );
	m_array[ 18 ].color = sf::Color( 0, 0, 0, 0 );
	m_array[ 19 ].color = sf::Color( 0, 0, 0, 0 );

	setTab( (ksAttackLogTab) m_current );
}

ksAttackLog::~ksAttackLog()
{
	delete [] m_text;
}

void ksAttackLog::toggle( std::string player_name, int player_hp, int player_max_hp, 
						 std::string enemy_name, int enemy_hp, int enemy_max_hp,
						 std::string original_track, std::string battle_track )
{
	if ( !m_toggle )
	{
		m_toggle = true;
		m_active = m_active ? false : true;
		m_current_frame = 0;

		m_original_track = original_track;
		m_battle_track = battle_track;

		m_player_hp = player_hp;
		m_enemy_hp = enemy_hp;

		m_player_max_hp = player_max_hp;
		m_enemy_max_hp = enemy_max_hp;

		m_text[ 4 ].setText( "Tiles/consolas_font_map.png", player_name, 800 - ( player_name.length() * 24 ), 544, sf::Color( 200, 0, 0, 255 ), 32 );
		m_text[ 5 ].setText( "Tiles/consolas_font_map.png", enemy_name, 24, 0, sf::Color( 200, 0, 0, 255 ), 32 );

		std::string player_temp = std::to_string( player_hp ) + '/' + std::to_string( player_max_hp );
		std::string enemy_temp = std::to_string( enemy_hp ) + '/' + std::to_string( enemy_max_hp );

		m_text[ 6 ].setText( "Tiles/consolas_font_map.png", player_temp, 800 - ( ( player_temp.length() - 1 ) * 43 ) - 64, 576, sf::Color( 200, 0, 0, 200 ), 64 );
		m_text[ 7 ].setText( "Tiles/consolas_font_map.png", enemy_temp, 0, 32, sf::Color( 200, 0, 0, 200 ), 64 );
	}
}

void ksAttackLog::modPlayerHP( int hp )
{
	m_player_hp += hp;

	std::string player_temp = std::to_string( m_player_hp ) + '/' + std::to_string( m_player_max_hp );
	m_text[ 6 ].setText( "Tiles/consolas_font_map.png", player_temp, 800 - ( ( player_temp.length() - 1 ) * 43 ) - 64, 576, sf::Color( 200, 0, 0, 200 ), 64 );
}

void ksAttackLog::modEnemyHP( ksPlayer & player, int hp )
{
	if ( ( m_enemy_hp + hp ) > 0 )
	{
		m_enemy_hp += hp;
		player.animate( 38, 38, 10 );

		std::string enemy_temp = std::to_string( m_enemy_hp ) + '/' + std::to_string( m_enemy_max_hp );
		m_text[ 7 ].setText( "Tiles/consolas_font_map.png", enemy_temp, 0, 32, sf::Color( 200, 0, 0, 200 ), 64 );
	}
	else
	{
		m_active = false;
		m_toggle = true;

		// For testing purposes reset the enemy's hp after death
		//m_enemy_hp = m_enemy_max_hp;
	}
}

int ksAttackLog::update( sf::View & map_view, ksAudioTrack & audio, ksPlayer & player, int logic, float player_x, float player_y )
{
	if ( m_toggle == true )
	{
		float temp = 0.f;

		if ( m_current_frame < FADE_OUT_FRAME_COUNT )
		{
			temp = (float) m_current_frame / (float) FADE_OUT_FRAME_COUNT;
			m_current_frame++;
		}
		else if ( m_current_frame < ( FADE_OUT_FRAME_COUNT + FADE_IN_FRAME_COUNT ) )
		{
			temp = ( FADE_IN_FRAME_COUNT - ( (float) m_current_frame - FADE_OUT_FRAME_COUNT ) ) / FADE_IN_FRAME_COUNT;
			m_current_frame++;
		}
		else
		{
			m_current_frame = 0;
			m_toggle = false;
		}
		if ( m_active )
		{
			m_array[ 16 ].color = sf::Color( 200, 0, 0, 255 * temp );
			m_array[ 17 ].color = sf::Color( 200, 0, 0, 255 * temp );
			m_array[ 18 ].color = sf::Color( 200, 0, 0, 255 * temp );
			m_array[ 19 ].color = sf::Color( 200, 0, 0, 255 * temp );
		}
		else
		{
			m_array[ 16 ].color = sf::Color( 0, 0, 0, 255 * temp );
			m_array[ 17 ].color = sf::Color( 0, 0, 0, 255 * temp );
			m_array[ 18 ].color = sf::Color( 0, 0, 0, 255 * temp );
			m_array[ 19 ].color = sf::Color( 0, 0, 0, 255 * temp );
		}
	}
	else if ( m_active )
	{
		if ( m_current_frame % 10 == 0 )
		{
			//player.animate( 37, 37, 10 );

			/*if ( m_array[ 16 ].color == sf::Color( 255, 0, 0, 80 ) )
			{
				m_array[ 16 ].color = sf::Color( 255, 0, 0, 100 );
				m_array[ 17 ].color = sf::Color( 255, 0, 0, 100 );
				m_array[ 18 ].color = sf::Color( 255, 0, 0, 100 );
				m_array[ 19 ].color = sf::Color( 255, 0, 0, 100 );
			}
			else
			{
				m_array[ 16 ].color = sf::Color( 255, 0, 0, 80 );
				m_array[ 17 ].color = sf::Color( 255, 0, 0, 80 );
				m_array[ 18 ].color = sf::Color( 255, 0, 0, 80 );
				m_array[ 19 ].color = sf::Color( 255, 0, 0, 80 );
			}*/
		}
	}

	if ( m_current_frame == 30 )
	{
		if ( m_active )
		{
			map_view.zoom( 0.5f );
			map_view.setCenter( player_x, player_y - 96 );
			logic = 2;

			audio.transitionTrack( m_battle_track );
		}
		else
		{
			map_view.zoom( 2.f );
			player.animate( 9, 9, 10 );
			logic = 0;

			audio.transitionTrack( m_original_track );
		}
	}

	return logic;
}

void ksAttackLog::setTab( ksAttackLogTab tab )
{
	m_current = tab;

	for ( int count = 0; count < 4; count++ )
	{
		if ( count == (int) tab )
		{
			m_array[ count * 4 ].color = sf::Color( 0, 0, 0, 180 );
			m_array[ ( count * 4 ) + 1 ].color = sf::Color( 0, 0, 0, 180 );
			m_array[ ( count * 4 ) + 2 ].color = sf::Color( 0, 0, 0, 180 );
			m_array[ ( count * 4 ) + 3 ].color = sf::Color( 0, 0, 0, 180 );
		}
		else
		{
			m_array[ count * 4 ].color = sf::Color( 0, 0, 0, 210 );
			m_array[ ( count * 4 ) + 1 ].color = sf::Color( 0, 0, 0, 210 );
			m_array[ ( count * 4 ) + 2 ].color = sf::Color( 0, 0, 0, 210 );
			m_array[ ( count * 4 ) + 3 ].color = sf::Color( 0, 0, 0, 210 );
		}
	}
}

void ksAttackLog::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_array, states );
}

void ksAttackLog::drawLog( sf::RenderWindow & app )
{
	if ( m_toggle || !m_active )
	{
		for ( int count = 0; count < 16; count++ )
			m_array[ count ].color = sf::Color( 0, 0, 0, 0 );

		app.draw( m_array );
	}
	else if ( m_active )
	{
		setTab( (ksAttackLogTab) m_current );

		app.draw( m_array );

		for ( int count = 0; count < 8; count++ )
			app.draw( m_text[ count ] );
	}
}
