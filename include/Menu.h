#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu();
	
	void drawMenu(sf::RenderWindow&);
	void drawLevelUp(sf::RenderWindow&);
	void drawGameOver(sf::RenderWindow&);

private:
	void createMenu();

	sf::Font m_font;
	sf::Text m_text;

	sf::Texture m_level1;
	sf::Texture m_level2;
	sf::Texture m_level3;
	sf::Texture m_exit;
	sf::Texture m_bg;

	sf::RectangleShape m_lvl1;
	sf::RectangleShape m_lvl2;
	sf::RectangleShape m_lvl3;
	sf::RectangleShape m_ex;
	sf::RectangleShape m_bgPic;

	std::vector <sf::Texture> m_texVec;
	std::vector <sf::RectangleShape> m_recVec;
	std::vector <sf::Texture> m_levelUpPics;
	std::vector <sf::RectangleShape> m_levelUpRecs;
};