/*********************************************
* Class: ksDrawableLayer	-	for SFML
*
* Purpose:
*	This class is part of the base elements
*	of the engine, so this class needs to be
*	changed in the event of future ports of
*	KingEngine.
*
*********************************************/

#ifndef KS_FILE_H
#define KS_FILE_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

class ksFile
{
public:
	ksFile();
	ksFile(sf::String filename);
	ksFile(sf::Text * debugText, sf::String filename);

	bool readFile(sf::String filename);
	int readInt();
	sf::String readString();
	sf::String readLine();

	void write(sf::String obj);
	void write(int obj);

	void writeLine(sf::String obj);
	void writeLine(int obj);

	bool endOfFile();

private:
	sf::String m_filename;
	bool is_open;

	int m_currentIndex;
	sf::String m_currentFile;

	sf::Text * m_debugText;
};

#endif