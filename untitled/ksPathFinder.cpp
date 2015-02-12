#include "ksPathFinder.h"
#include "ksPathNode.h"

ksPathFinder::ksPathFinder( ksPathNode * start, ksPathNode * end )
	: m_start( start ), m_end( end )
{ }

void ksPathFinder::start()
{

}

void ksPathFinder::update( std::vector<std::vector<int>> & events )
{
	if ( ! m_found )
		findPath();

	if ( m_found )
		tracePath();
}

void ksPathFinder::findPath()
{
	if ( m_checking->up != nullptr )
		determineValues( m_checking, m_checking->up );
	if ( m_checking->left != nullptr )
		determineValues( m_checking, m_checking->left );
	if ( m_checking->down != nullptr )
		determineValues( m_checking, m_checking->down );
	if  (m_checking->right != nullptr )
		determineValues( m_checking, m_checking->right );

	if ( ! m_found )
	{
		m_closed[ m_closed.size() + 1 ] = m_checking;
		std::map<int, struct ksPathNode *>::iterator iter;

		for ( iter = m_open.begin(); iter != m_open.end(); iter++ )
			if ( (*iter).second == m_checking )
				m_open.erase( (*iter).first );
	}
}

void ksPathFinder::determineValues( ksPathNode * current, ksPathNode * test )
{
	if ( test == nullptr )
		return;
	if ( test == m_end )
	{
		m_end->parent = current;
		m_found = true;
		return;
	}
	//if ( test == 
}

void ksPathFinder::tracePath()
{
}