#include "ksEngine.h"

using namespace luabind;

const float WALK_VELOCITY = 3.f;

ksEngine::ksEngine( char * mapfile, char * objfile, char * playerfile )
	:	m_app( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "KingEngine v0.1 Alpha", sf::Style::Titlebar | sf::Style::Close ),
	m_map( mapfile, "Maps/Voltor/voltor", 50, 40 ), m_layer( objfile ),
	m_player( playerfile, ksRect( 368, 288, 64, 64 ) ),
	m_text_log( "Tiles/consolas_font_map.png" ),
	m_map_view( sf::FloatRect( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) ),
	m_menu_view( sf::FloatRect( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) ),
	m_dialog_view( sf::FloatRect( 0, 0, 160, 128 ) ), m_dialog_active( false ),
	m_particles( sf::Color( 255, 0, 0, 200 ), sf::Vector2f( 64, 64 ), 4, 10, 5, 7 ), 
	m_foreground_particles( sf::Color( 0, 0, 255, 100 ), sf::Vector2f( -50.f, -50.f ), 6, 15, 20, 70 ),
	m_foreground_effect( sf::Color( 0, 0, 255, 100 ), sf::Color( 255, 255, 255, 0 ), 360, 10 ),
	m_fps_count( "Tiles/consolas_font_map.png", "", WINDOW_WIDTH - 32, 0 ), m_logic( PLAYER_ACTIVE ),
	m_back_track( "sorrow.ogg" ), m_map_switch_count( 0 ), m_map_switch( false )
{
	m_text_log.insert( "Welcome to the realm.", sf::Color::White );
	m_dialog_view.setViewport( sf::FloatRect( 0.f, 0.f, 0.2f, 0.2f ) );
}

ksEngine::ksEngine()
	: m_app( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "KingEngine v0.1 Alpha", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize ),
	m_map( "Tiles/Voltor/voltor.png", "Maps/Voltor/voltor", 25, 20 ),
	m_layer( "Tiles/Voltor/voltor_obj.png" ),
	m_player( "Tiles/Voltor/blacksmith.png", ksRect( 368, 288, 64, 64 ) ),
	m_text_log( "Tiles/consolas_font_map.png" ),
	m_map_view( sf::FloatRect( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) ),
	m_menu_view( sf::FloatRect( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT ) ),
	m_dialog_view( sf::FloatRect( 0, 0, 160, 128 ) ), m_dialog_active( false ),
	m_particles( sf::Color( 255, 0, 0, 200 ), sf::Vector2f( 64, 64 ), 4, 10, 5, 7 ), 
	m_foreground_particles( sf::Color( 0, 0, 255, 0 ), sf::Vector2f( -50.f, -50.f ), 6, 15, 20, 70 ),
	m_foreground_effect( sf::Color( 0, 0, 0, 0 ), sf::Color( 0, 0, 255, 120 ), 180, 180 ),
	m_fps_count( "Tiles/consolas_font_map.png", "", WINDOW_WIDTH - 32, 0 ), m_logic( PLAYER_ACTIVE ),
	m_back_track( "sorrow.ogg" ), m_map_switch_count( 0 ), m_map_switch( false )
{
	m_text_log.insert( "Welcome to KingEngine Alpha 0.1", sf::Color::White );

	m_dialog_view.setViewport( sf::FloatRect( 0.f, 0.f, 0.2f, 0.2f ) );
	m_dialog_view.zoom( 0.5f );
}

void ksEngine::Play()
{
	m_app.setFramerateLimit( 60 );

	bool keyDown[ 5 ] = { false };
	int current_tab = 0;

	runScript( "luafile.lua" );

	sf::Clock clock;

	while ( m_app.isOpen() )
	{
		sf::Event evt;

		while ( m_app.pollEvent( evt ) )
		{
			if ( evt.type == sf::Event::Closed )
				m_app.close();
			else if ( evt.type == sf::Event::KeyPressed )
			{
				if ( m_logic == PLAYER_ACTIVE )
				{
					if ( evt.key.code == sf::Keyboard::W )
						keyDown[ 0 ] = true;
					if ( evt.key.code == sf::Keyboard::S )
						keyDown[ 1 ] = true;
					if ( evt.key.code == sf::Keyboard::A )
						keyDown[ 2 ] = true;
					if ( evt.key.code == sf::Keyboard::D )
						keyDown[ 3 ] = true;
					if ( evt.key.code == sf::Keyboard::LShift || evt.key.code == sf::Keyboard::RShift )
						keyDown[ 4 ] = true;
					if ( evt.key.code == sf::Keyboard::Num1 )
					{
						m_back_track.transitionTrack( "sorrow.ogg" );
						m_text_log.insert( "ksEngine: Changing track to sorrow...", sf::Color( 0, 255, 0, 255 ) );
					}
					if ( evt.key.code == sf::Keyboard::Num2 )
					{
						m_back_track.transitionTrack( "dream_of_the_sequence.ogg" );
						m_text_log.insert( "ksEngine: Changing track to dream...", sf::Color( 0, 255, 0, 255 ) );
					}
					if ( evt.key.code == sf::Keyboard::Return )
						m_text_log.activate();

					if ( evt.key.code == sf::Keyboard::Left )
					{
						m_map_view.rotate( 1 );
						m_menu_view.rotate( 1 );
						m_dialog_view.rotate( 1 );
					}
					else if ( evt.key.code == sf::Keyboard::Right )
					{
						m_map_view.rotate( -1 );
						m_menu_view.rotate( -1 );
						m_dialog_view.rotate( -1 );
					}
				}
				else
				{
					if ( evt.key.code == sf::Keyboard::Left || evt.key.code == sf::Keyboard::A )
						current_tab = current_tab > 0 ? current_tab - 1 : 3;
					else if ( evt.key.code == sf::Keyboard::Right || evt.key.code == sf::Keyboard::D )
						current_tab = current_tab < 3 ? current_tab + 1 : 0;
					else if ( evt.key.code == sf::Keyboard::Down || evt.key.code == sf::Keyboard::S ||
						evt.key.code == sf::Keyboard::Up || evt.key.code == sf::Keyboard::W )
						current_tab = current_tab > 1 ? current_tab - 2 : current_tab + 2;
				}

				if ( m_logic == MENU_ACTIVE )
				{
					m_menu.setTab( (ksMenuTab) current_tab );

					if ( evt.key.code == sf::Keyboard::Return )
						m_menu.levelUp();
				}
				else if ( m_logic == BATTLE_ACTIVE )
				{
					m_attack_log.setTab( (ksAttackLogTab) current_tab );

					if ( evt.key.code == sf::Keyboard::Return )
						if ( current_tab == 0 )
							m_attack_log.modEnemyHP( m_player, -5 );
				}
				else if ( m_logic == DIALOG_ACTIVE )
				{
					if ( evt.key.code == sf::Keyboard::Return )
						m_text_log.activate();
				}

				if ( evt.key.code == sf::Keyboard::L )
					m_logic = m_logic == MENU_ACTIVE ? PLAYER_ACTIVE : MENU_ACTIVE;
				else if ( evt.key.code == sf::Keyboard::K )
				{
					current_tab = 0;
					//m_foreground_effect.set( 0, sf::Color( 255, 0, 0, 120 ), sf::Color( 0, 255, 0, 120 ), 5, 5 );
					m_player.animate( 9, 9, 30 );
					//m_back_track.transitionTrack( "dbz.ogg" );
					m_attack_log.toggle( "Blacksmith", 20, 20, "Goblin", 20, 20, "sorrow.ogg", "dbz.ogg" );
				}
			}
			else if ( evt.type == sf::Event::KeyReleased )
			{
				if ( m_logic == PLAYER_ACTIVE )
				{
					if ( evt.key.code == sf::Keyboard::W )
						keyDown[ 0 ] = false;
					if ( evt.key.code == sf::Keyboard::S )
						keyDown[ 1 ] = false;
					if ( evt.key.code == sf::Keyboard::A )
						keyDown[ 2 ] = false;
					if ( evt.key.code == sf::Keyboard::D )
						keyDown[ 3 ] = false;
					if ( evt.key.code == sf::Keyboard::LShift )
						keyDown[ 4 ] = false;
				}
			}
		}
		if ( m_logic == PLAYER_ACTIVE && ! m_dialog_active && ! m_map_switch )
		{
			float temp = WALK_VELOCITY;

			if ( keyDown[ 4 ] )
				temp = WALK_VELOCITY * 2;

			if ( keyDown[ 0 ] )
				m_player.changeVelY( -temp );
			if ( keyDown[ 1 ] )
				m_player.changeVelY( temp );
			if ( keyDown[ 2 ] )
				m_player.changeVelX( -temp );
			if ( keyDown[ 3 ] )
				m_player.changeVelX( temp );

			int temp_script = m_player.moveObject( m_map_view, m_map );

			if ( temp_script > 1 )
				runScript( m_map.getMapName() + "_" + std::to_string( temp_script ) + ".lua" );
		}
		else
			m_player.setVelocity( 0, 0 );

		// Center and bound the camera
		if ( m_logic == PLAYER_ACTIVE )
			boundCamera();

		m_particles.setColor( sf::Color( 0, 0, 0, 0 ) );

		// Load LUA file if one is in queue
		loadScript();

		m_particles.update();
		m_foreground_particles.update();
		m_foreground_effect.update();
		m_text_log.update( m_dialog_active, 60 );
		m_back_track.update();
		m_logic = (GameMode) m_attack_log.update( m_map_view, m_back_track, m_player, m_logic, m_player.getX( m_map_view ), m_player.getY( m_map_view ) );

		//m_dialog_view.setCenter( m_player.getX( m_map_view ) + 32, m_player.getY( m_map_view ) + 32 );

		// Draw the engine to screen
		drawEngine();
		int fps = 1 / clock.restart().asSeconds();
		m_fps_count.setText( "Tiles/consolas_font_map.png", std::to_string( fps ), WINDOW_WIDTH - 32, 0 );
	}
}

void ksEngine::setLUA( lua_State *& luastate )
{
	luabind::module( luastate ) [ 

		def( "random", &std::rand ),

		luabind::class_<ksEngine>( "Engine" )
			.def( "runScript", &ksEngine::setScript )
			.def( "activateDialog", &ksEngine::activateDialog ),

			luabind::class_<ksMenu>( "Menu" )
			.def( "level_up", &ksMenu::levelUp )
			.def_readwrite( "name", &ksMenu::NAME )
			.def_readwrite( "level", &ksMenu::LEVEL )
			.def_readwrite( "hp", &ksMenu::HP )
			.def_readwrite( "max_hp", &ksMenu::MAX_HP )
			.def_readwrite( "xp", &ksMenu::XP )
			.def_readwrite( "xp_to_next", &ksMenu::XP_TO_NEXT )
			.def_readwrite( "att_high",  &ksMenu::ATT_HIGH )
			.def_readwrite( "att_low", &ksMenu::ATT_LOW )
			.def_readwrite( "def", &ksMenu::DEF ),

			luabind::class_<sf::View>( "View" )
			.def( constructor<sf::Vector2f, sf::Vector2f>() ),

			luabind::class_<ksRect>( "ksRect" )
			.def( constructor<float, float, float, float>() )
			.def_readwrite( "x", &ksRect::x )
			.def_readwrite( "y", &ksRect::y )
			.def_readwrite( "w", &ksRect::w )
			.def_readwrite( "h", &ksRect::h ),

			luabind::class_<ksMap>( "ksMap" )
			.def( "load", &ksMap::load ),

			luabind::class_<ksAbstract>( "ksAbstract" )
			.def( constructor<ksRect, int>() )
			.def( "animate", &ksAbstract::animate )
			.def( "getPosition", &ksAbstract::getPosition )
			.def( "getTexture", &ksAbstract::getTexture )
			.def( "setAnimationLow", &ksAbstract::setAnimationLow )
			.def( "setAnimationHigh", &ksAbstract::setAnimationHigh )
			.def( "setAnimationSpeed", &ksAbstract::setAnimationSpeed ),

			luabind::class_<ksAbstractLayer>( "ksAbstractLayer" )
			.def( constructor<std::string>() )
			.def( "setFile", &ksAbstractLayer::setTileSheet )
			.def( "addObject", &ksAbstractLayer::addObject )
			.def( "animate", &ksAbstractLayer::animate )
			.def( "getRect", &ksAbstractLayer::getRect )
			.def( "getCount", &ksAbstractLayer::getCount )
			.def( "clear", &ksAbstractLayer::purge ),

			luabind::class_<ksPlayer>( "ksPlayer" )
			.def( constructor<std::string, ksRect>() )
			.def( "x", &ksPlayer::getX )
			.def( "y", &ksPlayer::getY )
			.def( "getVelocity", &ksPlayer::getVelocity )
			.def( "setPosition", &ksPlayer::setPlayerPosition ),

			luabind::class_<ksTextLog>( "ksTextLog" )
			.def( "insert", &ksTextLog::insert ),

			luabind::class_<sf::Color>( "Color" )
			.def( constructor<int, int, int, int>() ),

			luabind::class_<sf::Vector2f>( "Vector2f" )
			.def( constructor<float, float>() ),

			luabind::class_<ksEffect>( "Effect" )
			.def( constructor<sf::Color, sf::Color, int, int>() )
			.def( "add", &ksEffect::add )
			.def( "clear", &ksEffect::clear )
			.def( "resize", &ksEffect::resizeMap )
			.def( "set", &ksEffect::set ),

			luabind::class_<ksParticleEngine>( "Particles" )
			.def( constructor<sf::Color, sf::Vector2f, int, int, int, int>() )
			.def( "setColor", &ksParticleEngine::setColor )
			.def( "setSize", &ksParticleEngine::setSize )
			.def( "setNumber", &ksParticleEngine::setNumber )
			.def( "setVelocity", &ksParticleEngine::setVelocity )
			.def( "setReach", &ksParticleEngine::setReach ),

			luabind::class_<ksAudioTrack>( "Audio" )
			.def( "transition", &ksAudioTrack::transitionTrack )
	];

	luabind::globals( luastate ) [ "MapView" ] = &m_map_view;
	luabind::globals( luastate ) [ "Player" ] = &m_player;
	luabind::globals( luastate ) [ "AdventureLog" ] = &m_text_log;
	luabind::globals( luastate ) [ "ObjectLayer" ] = &m_layer;
	luabind::globals( luastate ) [ "Map" ] = &m_map;
	luabind::globals( luastate ) [ "Status" ] = &m_menu;
	luabind::globals( luastate ) [ "ForegroundEffect" ] = &m_foreground_effect;
	luabind::globals( luastate ) [ "ForegroundParticles" ] = &m_foreground_particles;
	luabind::globals( luastate ) [ "BackgroundParticles" ] = &m_particles;
	luabind::globals( luastate ) [ "AudioTrack" ] = &m_back_track;
	luabind::globals( luastate ) [ "KingEngine" ] = this;
}

void ksEngine::setScript( std::string filename )
{
	m_map_switch_file = filename;
	m_map_switch = true;
	m_map_switch_count = 0;
}

void ksEngine::loadScript()
{
	if ( ( m_map_switch == true ) && ( m_map_switch_count == 30 ) )
		runScript( m_map_switch_file );
}

void ksEngine::runScript( std::string filename )
{
	// Setup LUA
	lua_State * lua_state = luaL_newstate();

	luaopen_base( lua_state );
	luaopen_io( lua_state );
	luaopen_string( lua_state );
	luaopen_math( lua_state );

	luabind::open( lua_state );

	setLUA( lua_state );

	bool lua_success = luaL_dofile( lua_state, filename.c_str() ) || lua_pcall( lua_state, 0, 0, 0 );

	if ( ! lua_success )
		m_text_log.insert( "--- ksEngine: COULD NOT LOAD " + (std::string) filename, sf::Color::Red );

	lua_close( lua_state );
}

void ksEngine::boundCamera()
{
	// Center the camera
	m_map_view.setCenter( m_player.getPosition().x + ( m_map_view.getSize().x / 2 ),
		m_player.getPosition().y + ( m_map_view.getSize().y / 2 ) );

	// Bound the camera
	if ( m_map_view.getCenter().x - ( m_map_view.getSize().x / 2 ) < 0 )
		m_map_view.setCenter( m_map_view.getSize().x / 2, m_map_view.getCenter().y );

	if ( m_map_view.getCenter().y - ( m_map_view.getSize().y / 2 ) < 0 )
		m_map_view.setCenter( m_map_view.getCenter().x, m_map_view.getSize().y / 2 );

	if ( m_map_view.getCenter().x + ( m_map_view.getSize().x / 2 ) > ( m_map.getWidth() * 32 ) )
		m_map_view.setCenter( ( m_map.getWidth() * 32 ) - ( m_map_view.getSize().x / 2 ), m_map_view.getCenter().y );

	if ( m_map_view.getCenter().y + ( m_map_view.getSize().y / 2 ) > ( m_map.getHeight() * 32 ) )
		m_map_view.setCenter( m_map_view.getCenter().x, ( m_map.getHeight() * 32 ) - ( m_map_view.getSize().y / 2 ) );
}

void ksEngine::drawEngine()
{
	m_app.clear();

	m_app.setView( m_map_view );

	// Draw Map
	m_app.draw( m_map );

	// Draw Object Layer
	m_layer.drawLayer( m_app );

	// Draw Player
	m_app.draw( m_player );

	// Draw Particles
	m_app.draw( m_particles );

	// Draw Foreground Effect ( weather )
	m_app.draw( m_foreground_effect );

	m_app.setView( m_menu_view );

	// Draw Foreground Particles ( weather )
	m_app.draw( m_foreground_particles );


	// Draw either the TextLog or the Menu
	if ( m_logic == PLAYER_ACTIVE )
		m_text_log.drawLog( m_app );
	else if ( m_logic == MENU_ACTIVE )
		m_menu.drawMenu( m_app );

	m_attack_log.drawLog( m_app );

	m_app.draw( m_fps_count );

	if ( m_map_switch )
	{
		float temp = 0.f;
		m_map_switch_count++;

		if ( m_map_switch_count <= 30 )
			temp = (float) m_map_switch_count / 30.f;
		else if ( m_map_switch_count <= 60 )
			temp = ( 30.f - ( (float) m_map_switch_count - 30.f ) ) / 30.f;
		else
		{
			m_map_switch_count = 0;
			m_map_switch = false;
		}

		sf::RectangleShape fill_screen( sf::Vector2f( 800, 640 ) );
		fill_screen.setFillColor( sf::Color( 0, 0, 0, 255 * temp ) );

		m_app.draw( fill_screen );
	}

	if ( m_dialog_active )
	{
		sf::RectangleShape rect_shape( sf::Vector2f( 160, 128 ) );
		rect_shape.setPosition( 0, 0 );
		rect_shape.setFillColor( sf::Color( 0, 0, 0, 0 ) );
		rect_shape.setOutlineThickness( 1 );
		rect_shape.setOutlineColor( sf::Color( 0, 0, 0, 255 ) );

		m_app.draw( rect_shape );

		//m_text_log.setLogPosition( 160, 0 );

		m_app.setView( m_dialog_view );

		m_app.draw( m_map );
		m_layer.drawLayer( m_app );
		m_app.draw( m_player );
		m_app.draw( m_particles );
		m_app.draw( m_foreground_effect );
	}

	m_app.display();
}

void ksEngine::activateDialog( std::string text, sf::Color color, sf::Vector2f center )
{
	m_dialog_view.setCenter( center );
	m_dialog_active = true;

	m_text_log.clear();
	m_text_log.setLogPosition( 160, 0 );
	m_text_log.insert( text, color );
}