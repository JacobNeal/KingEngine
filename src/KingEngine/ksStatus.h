#ifndef KS_STATUS_H
#define KS_STATUS_H

#include "ksFile.h"
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

	inline ksItem & Item(int index);
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
	ksFile file("player_status.txt");

	m_name = file.readLine();
	m_level = file.readInt();
	m_hp = file.readInt();
	m_xp = file.readInt();
	m_xp_to_next = file.readInt();

	m_max_hp = 16 + (m_level * 4);
	m_att_low = m_level;
	m_att_high = 4 + m_level;
	m_def = 4 + m_level;

	m_equipment = new ksItem[5];

	file.readFile("player_equip.txt");

	for (int count = 0; count < 5; count++)
	{
		m_equipment[count].NAME() = file.readLine();
		m_equipment[count].DESC() = file.readLine();
		m_equipment[count].SCRIPT() = file.readLine();
	}
}

inline void ksStatus::LevelUp()
{
	m_xp += ((2 * m_level) + 3) * (m_level + 3);
	m_level++;
	m_xp_to_next = ((2 * m_level) + 3) * (m_level + 3);

	m_att_low++;
	m_att_high++;
	m_def++;
	m_max_hp += 4;
}

inline ksStatus::~ksStatus()
{
	ksFile file("player_status.txt");

	file.writeLine(m_name);
	file.writeLine(m_level);
	file.writeLine(m_hp);
	file.writeLine(m_xp);
	file.writeLine(m_xp_to_next);

	file.readFile("player_equip.txt");

	for (int count = 0; count < 5; count++)
	{
		file.writeLine(m_equipment[count].NAME());
		file.writeLine(m_equipment[count].DESC());
		file.writeLine(m_equipment[count].SCRIPT());
	}

	delete[] m_equipment;
}

inline ksItem & ksStatus::Item(int index)
{
	return m_equipment[index];
}

#endif