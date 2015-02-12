#ifndef KS_STATUS_H
#define KS_STATUS_H

#include <fstream>
#include <string>
#include "ksItem.h"

class ksStatus
{
	public:
		inline ksStatus();
		inline ~ksStatus();

		std::string & NAME() { return m_name; }
		int & LEVEL() { return m_level; }
		int & HP() { return m_hp; }
		int & MAX_HP() { return m_max_hp; }
		int & XP() { return m_xp; }
		int & XP_TO_NEXT() { return m_xp_to_next; }
		int & ATT_HIGH() { return m_att_high; }
		int & ATT_LOW() { return m_att_low; }
		int & DEF() { return m_def; }

		inline ksItem & Item( int index );
		inline void LevelUp();

	private:
		std::string m_name;
		int m_level;
		int m_hp;
		int m_max_hp;
		int m_xp;
		int m_xp_to_next;
		int m_att_high;
		int m_att_low;
		int m_def;

		ksItem * m_equipment;
};

inline ksStatus::ksStatus()
{
	std::ifstream file( "player_status.txt" );

	if ( file.is_open() )
	{
		getline( file, m_name );
		file >> m_level;
		file >> m_hp;
		file >> m_xp;
		file >> m_xp_to_next;

		file.close();
	}

	m_max_hp = 16 + ( m_level * 4 );
	m_att_low = m_level;
	m_att_high = 4 + m_level;
	m_def = 4 + m_level;

	m_equipment = new ksItem[ 5 ];

	file.open( "player_equip.txt" );

	if ( file.is_open() )
	{
		std::string temp_name;
		std::string temp_desc;
		std::string temp_script;

		for ( int count = 0; count < 5; count++ )
		{
			getline( file, temp_name );
			getline( file, temp_desc );
			getline( file, temp_script );

			m_equipment[ count ].NAME() = temp_name;
			m_equipment[ count ].DESC() = temp_desc;
			m_equipment[ count ].SCRIPT() = temp_script;
		}

		file.close();
	}
}

inline void ksStatus::LevelUp()
{
	m_xp += ( ( 2 * m_level ) + 3 ) * ( m_level + 3 );
	m_level++;
	m_xp_to_next = ( ( 2 * m_level ) + 3 ) * ( m_level + 3 );

	m_att_low++;
	m_att_high++;
	m_def++;
	m_max_hp += 4;
}

inline ksStatus::~ksStatus()
{
	std::ofstream file( "player_status.txt" );

	if ( file.is_open() )
	{
		file << m_name << '\n';
		file << m_level << '\n';
		file << m_hp << '\n';
		file << m_xp << '\n';
		file << m_xp_to_next << '\n';

		file.close();
	}

	file.open( "player_equip.txt" );

	if ( file.is_open() )
	{
		for ( int count = 0; count < 5; count++ )
		{
			file << m_equipment[ count ].NAME() << '\n'
				 << m_equipment[ count ].DESC() << '\n'
				 << m_equipment[ count ].SCRIPT() << '\n';
		}

		file.close();
	}

	delete [] m_equipment;
}

inline ksItem & ksStatus::Item( int index )
{
	return m_equipment[ index ];
}

#endif