#include "ksMenu.h"

#define TAB_OPACITY 180
#define MENU_OPACITY 180
#define TAB_WIDTH 200.f
#define TAB_INC 30

ksMenu::ksMenu()
	:	m_tab( ITEMS ), m_text_num( 11 )
{
	m_text = new ksText[ 11 ];
	std::string font = "Tiles/consolas_font_map.png";

	m_text[ 0 ].setText( font, "Status", 32, 32 );
	m_text[ 1 ].setText( font, "Items", 232, 32 );
	m_text[ 2 ].setText( font, "Equip", 432, 32 );
	m_text[ 3 ].setText( font, "Quest", 632, 32 );

	// Status Tab
	m_text[ 4 ].setText( font, m_status.NAME() + " ( Level: " + std::to_string( m_status.LEVEL() ) + " )", 32, 96 );
	m_text[ 5 ].setText( font, "Health:         " + std::to_string( m_status.HP() ) + "/" + std::to_string( m_status.MAX_HP() ), 32, 128 );
	m_text[ 7 ].setText( font, "XP:             " + std::to_string( m_status.XP() ), 32, 192 );
	m_text[ 8 ].setText( font, "XP to Next:     " + std::to_string( m_status.XP_TO_NEXT() ), 32, 224 );
	m_text[ 9 ].setText( font, "Attack Rating:  " + std::to_string( m_status.ATT_HIGH() ), 32, 256 );
	m_text[ 10 ].setText( font, "Defense Rating: " + std::to_string( m_status.DEF() ), 32, 288 );

	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( 20 );

	// Status Tab
	m_array[ 0 ].position = sf::Vector2f( 0.f, 0.f );
	m_array[ 1 ].position = sf::Vector2f( TAB_WIDTH, 0.f );
	m_array[ 2 ].position = sf::Vector2f( TAB_WIDTH, 64.f );
	m_array[ 3 ].position = sf::Vector2f( 0.f, 64.f );

	// Items Tab
	m_array[ 4 ].position = sf::Vector2f( 200.f, 0.f );
	m_array[ 5 ].position = sf::Vector2f( 200.f + TAB_WIDTH, 0.f );
	m_array[ 6 ].position = sf::Vector2f( 200.f + TAB_WIDTH, 64.f );
	m_array[ 7 ].position = sf::Vector2f( 200.f, 64.f );

	// Equip Tab
	m_array[ 8 ].position = sf::Vector2f( 400.f, 0.f );
	m_array[ 9 ].position = sf::Vector2f( 400.f + TAB_WIDTH, 0.f );
	m_array[ 10 ].position = sf::Vector2f( 400.f + TAB_WIDTH, 64.f );
	m_array[ 11 ].position = sf::Vector2f( 400.f, 64.f );

	// Quest Tab
	m_array[ 12 ].position = sf::Vector2f( 600.f, 0.f );
	m_array[ 13 ].position = sf::Vector2f( 600.f + TAB_WIDTH, 0.f );
	m_array[ 14 ].position = sf::Vector2f( 600.f + TAB_WIDTH, 64.f );
	m_array[ 15 ].position = sf::Vector2f( 600.f, 64.f );

	// Main
	m_array[ 16 ].position = sf::Vector2f( 0.f, 64.f );
	m_array[ 17 ].position = sf::Vector2f( 800.f, 64.f );
	m_array[ 18 ].position = sf::Vector2f( 800.f, 640.f );
	m_array[ 19 ].position = sf::Vector2f( 0.f, 640.f );

	m_array[ 16 ].color = sf::Color( 0, 0, 0, 180 );
	m_array[ 17 ].color = sf::Color( 0, 0, 0, 180 );
	m_array[ 18 ].color = sf::Color( 0, 0, 0, 180 );
	m_array[ 19 ].color = sf::Color( 0, 0, 0, 180 );

	// Default Tab
	setTab( STATUS );
}

ksMenu::~ksMenu()
{
	delete [] m_text;
}

void ksMenu::setTab( ksMenuTab tab )
{
	std::string font = "Tiles/consolas_font_map.png";
	ksText * temp = new ksText[ m_text_num ];
	std::string str_temp;

	temp[ 0 ].setText( font, "Status", 32, 32 );
	temp[ 1 ].setText( font, "Items", 232, 32 );
	temp[ 2 ].setText( font, "Equip", 432, 32 );
	temp[ 3 ].setText( font, "Quest", 632, 32 );

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

	if ( m_tab != STATUS && tab == STATUS )
	{
		temp[ 4 ].setText( font, m_status.NAME() + " ( Level: " + std::to_string( m_status.LEVEL() ) + " )", 32, 96 );
		temp[ 5 ].setText( font, "Health:         " + std::to_string( m_status.HP() ) + "/" + std::to_string( m_status.MAX_HP() ), 32, 128 );
		temp[ 7 ].setText( font, "XP:             " + std::to_string( m_status.XP() ), 32, 160 );
		temp[ 8 ].setText( font, "XP to Next:     " + std::to_string( m_status.XP_TO_NEXT() ), 32, 192 );
		temp[ 9 ].setText( font, "Attack Rating:  " + std::to_string( m_status.ATT_HIGH() ), 32, 224 );
		temp[ 10 ].setText( font, "Defense Rating: " + std::to_string( m_status.DEF() ), 32, 256 );
	}
	else if ( m_tab != ITEMS && tab == ITEMS )
	{
		for ( int count = 4; count < m_text_num && ( count - 4 ) < m_inventory.getNumberItems(); count++ )
			temp[ count ].setText( font, m_inventory.Item( count - 4 ).NAME() + "        " + m_inventory.Item( count - 4 ).DESC(), 32, ( ( count - 4 ) * 32 ) + 96 );
	}
	else if ( m_tab != EQUIP && tab == EQUIP )
	{
		temp[ 4 ].setText( font, "Weapon: " + m_status.Item( 0 ).NAME(), 32, 96 );
		temp[ 5 ].setText( font, "Head: " + m_status.Item( 1 ).NAME(), 32, 128 );
		temp[ 6 ].setText( font, "Body: " + m_status.Item( 2 ).NAME(), 32, 160 );
		temp[ 7 ].setText( font, "Legs: " + m_status.Item( 3 ).NAME(), 32, 192 );
		temp[ 8 ].setText( font, "Accessory: " + m_status.Item( 4 ).NAME(), 32, 224 );
	}
	else if ( m_tab != QUEST && tab == QUEST )
	{
		std::ifstream file( "player_quest.txt" );

		if ( file.is_open() )
		{
			for ( int count = 4; count < m_text_num && !file.eof(); count++ )
			{
					getline( file, str_temp );
					temp[ count ].setText( font, str_temp, 32, ( ( count - 4 ) * 32 ) + 96 );
			}

			file.close();
		}
	}

	delete [] m_text;
	m_text = temp;

	m_tab = tab;
}

void ksMenu::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_array, states );
}

void ksMenu::drawMenu( sf::RenderWindow & app )
{
	app.draw( *this );

	for ( int count = 0; count < m_text_num; count++ )
		app.draw( m_text[ count ] );
}