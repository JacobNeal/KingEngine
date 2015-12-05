#ifndef KS_MENU_H
#define KS_MENU_H

#include "ksDrawable.h"
#include "ksRenderWindow.h"
#include "ksInventory.h"
#include "ksStatus.h"
#include "ksText.h"

enum ksMenuTab { STATUS, ITEMS, EQUIP, QUEST };

class ksMenu : public ksDrawable
{
public:
	ksMenu();
	~ksMenu();
	void setTab(ksMenuTab tab);
	//virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void drawMenu(ksRenderWindow & app);

	void levelUp() { m_status.LevelUp(); }
	std::string & NAME() { return m_status.NAME(); }
	int & LEVEL(int level) { return m_status.LEVEL(); }
	int & HP(int hp) { return m_status.HP(); }
	int & MAX_HP(int max_hp) { return m_status.MAX_HP(); }
	int & XP(int xp) { return m_status.XP(); }
	int & XP_TO_NEXT(int xp_to_next) { return m_status.XP_TO_NEXT(); }
	int & ATT_HIGH(int att_high) { return m_status.ATT_HIGH(); }
	int & ATT_LOW(int att_low) { return m_status.ATT_LOW(); }
	int & DEF(int def) { return m_status.DEF(); }

private:
	//sf::VertexArray m_array;
	ksMenuTab m_tab;

	ksStatus m_status;
	ksInventory m_inventory;

	int m_text_num;
	ksText * m_text;
};

#endif