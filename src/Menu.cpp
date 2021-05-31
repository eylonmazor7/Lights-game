#include "Menu.h"
#include "Utilities.h"
#include <Windows.h>

Menu::Menu()
{
	createMenu(); 
}

void Menu::createMenu()
{
	m_texVec.resize(5);
	m_recVec.resize(5);
	m_levelUpPics.resize(5);
	m_levelUpRecs.resize(5);

	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			m_texVec[i].loadFromFile("menuPic1.png");
			m_levelUpPics[i].loadFromFile("bulb.png");
			break;
		case 1:
			m_texVec[i].loadFromFile("level1.png");
			m_levelUpPics[i].loadFromFile("goodjob.png");
			break;
		case 2:
			m_texVec[i].loadFromFile("level22.png");
			m_levelUpPics[i].loadFromFile("levelup.png");
			break;
		case 3:
			m_texVec[i].loadFromFile("level33.png");
			m_levelUpPics[i].loadFromFile("youwin.png");
			break;
		case 4:
			m_texVec[i].loadFromFile("exit.png");
			m_levelUpPics[i].loadFromFile("party.png");
			break;

		default:
			break;
		}
		m_texVec[i].setSmooth(true);
		m_recVec[i].setTexture(&m_texVec[i]);

		m_levelUpPics[i].setSmooth(true);
		m_levelUpRecs[i].setTexture(&m_levelUpPics[i]);
		
	}

	m_font.loadFromFile("Coquin.TTF");
	m_text.setFont(m_font);
	m_text.setString("Lights");
	m_text.setCharacterSize(110);
	m_text.setPosition(140, 60);
	m_text.setFillColor(sf::Color::Yellow);
}

void Menu::drawMenu(sf::RenderWindow& window)
{

	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			m_recVec[i].setSize(sf::Vector2f(Utilities::WINDOW_SIZE, Utilities::WINDOW_SIZE));
			break;
		default:
			m_recVec[i].setSize(sf::Vector2f(Utilities::ICON_SIZE, Utilities::ICON_SIZE));
			m_recVec[i].setPosition(90 * i, 350);
			break;
		}
		window.draw(m_recVec[i]);
	}
	window.draw(m_text);
}

void Menu::drawLevelUp(sf::RenderWindow& window)
{
	window.clear();
	m_levelUpRecs[4].setSize(sf::Vector2f(500, 500));
	window.draw(m_levelUpRecs[4]);
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			m_levelUpRecs[i].setSize(sf::Vector2f(100, 95));
			m_levelUpRecs[i].setPosition(130, 130);
			break;
			
		case 1:
			m_levelUpRecs[i].setSize(sf::Vector2f(80, 95));
			m_levelUpRecs[i].setPosition(260, 130);
			break;

		case 2:
			m_levelUpRecs[i].setSize(sf::Vector2f(230, 105));
			m_levelUpRecs[i].setPosition(130, 230);
			break;
		default:
			break;
		}
		window.draw(m_levelUpRecs[i]);
	}
	window.display();
	Sleep(Utilities::SLEEP_TIME);
}

void Menu::drawGameOver(sf::RenderWindow& window)
{
	sf::Text text1;
	text1.setFont(m_font);
	window.clear();
	m_levelUpRecs[4].setSize(sf::Vector2f(500, 500));
	window.draw(m_levelUpRecs[4]);

	m_levelUpRecs[3].setSize(sf::Vector2f(250, 180));
	m_levelUpRecs[3].setPosition(125, 100);
	window.draw(m_levelUpRecs[3]);

	text1.setString("You Did It! Back To Main Menu");
	text1.setFillColor(sf::Color::Blue);
	text1.setPosition(60, 320);
	text1.setCharacterSize(35);

	window.draw(text1);
	window.display();
	Sleep(Utilities::SLEEP_TIME);
}