#ifndef KS_PATH_FINDER_H
#define KS_PATH_FINDER_H

#include <map>
#include <vector>
#include "ksPathNode.h"

class ksPathFinder
{
	public:
		ksPathFinder( struct ksPathNode * start, struct ksPathNode * end );
		void start();
		void update( std::vector<std::vector<int>> & events );

	private:
		void findPath();
		void determineValues( struct ksPathNode * current, struct ksPathNode * test );
		void tracePath();

		std::map<int, struct ksPathNode *> m_open;
		std::map<int, struct ksPathNode *> m_closed;
		std::map<int, struct ksPathNode *> m_path;
		
		struct ksPathNode * m_start;
		struct ksPathNode * m_end;
		struct ksPathNode * m_checking;

		bool m_found;
};

#endif