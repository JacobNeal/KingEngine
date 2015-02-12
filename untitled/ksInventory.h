#ifndef KS_INVENTORY_H
#define KS_INVENTORY_H

#include <vector>
#include <fstream>
#include "ksItem.h"

class ksInventory
{
	public:
		inline ksInventory();
		inline ksItem & Item( int index );

		int getNumberItems() { return m_items.size(); }

	private:
		std::vector<ksItem> m_items;
};

inline ksInventory::ksInventory()
{
	std::ifstream file( "player_items.txt" );

	std::string temp_name;
	std::string temp_desc;
	std::string temp_script;
	
	if ( file.is_open() )
	{
		while ( !file.eof() )
		{
			getline( file, temp_name );
			getline( file, temp_desc );
			getline( file, temp_script );

			m_items.push_back( ksItem( temp_name, temp_desc, temp_script ) );
		}

		file.close();
	}
}

inline ksItem & ksInventory::Item( int index )
{
	return m_items[ index ];
}

#endif