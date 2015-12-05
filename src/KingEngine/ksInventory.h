#ifndef KS_INVENTORY_H
#define KS_INVENTORY_H

#include <vector>
#include "ksFile.h"
#include "ksItem.h"

class ksInventory
{
public:
	inline ksInventory();
	inline ksItem & Item(int index);

	int getNumberItems() { return m_items.size(); }

private:
	std::vector<ksItem> m_items;
};

inline ksInventory::ksInventory()
{
	ksFile file("player_items.txt");

	std::string temp_name;
	std::string temp_desc;
	std::string temp_script;

	while (!file.endOfFile())
	{
		temp_name = file.readLine();
		temp_desc = file.readLine();
		temp_script = file.readLine();

		m_items.push_back(ksItem(temp_name, temp_desc, temp_script));
	}
}

inline ksItem & ksInventory::Item(int index)
{
	return m_items[index];
}

#endif