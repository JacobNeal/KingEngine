#ifndef KS_ITEM_H
#define KS_ITEM_H

#include <fstream>
#include <string>

class ksItem
{
	public:
		inline ksItem();
		inline ksItem( std::string name, std::string desc, std::string script );
		inline ksItem( std::string filename );

		inline void read( std::string filename );

		std::string & NAME() { return m_name; }
		std::string & DESC() { return m_description; }
		std::string & SCRIPT() { return m_script; }

	private:
		std::string m_name;
		std::string m_description;
		std::string m_script;
};

inline ksItem::ksItem()
	: m_name( "Name" ), m_description( "Desc" ), m_script( "Script" )
{ }

inline ksItem::ksItem( std::string name, std::string desc, std::string script )
	: m_name( name ), m_description( desc ), m_script( script )
{ }

inline ksItem::ksItem( std::string filename )
{
	read( filename );
}

inline void ksItem::read( std::string filename )
{
	std::ifstream file( filename );

	if ( file.is_open() )
	{
		getline( file, m_name );
		getline( file, m_description );
		getline( file, m_script );

		file.close();
	}
}

#endif