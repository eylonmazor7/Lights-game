#pragma once
#include <list>
#include "Point.h"
#include "Board.h"
#include <vector>
#include <SFML/Audio.hpp>
#include "Menu.h"

class Controller
{
public:
	Controller() {}
	void startGame();
	
private:
	void startGameMenu(sf::RenderWindow&);
	bool isMouseOverIcon(sf::RenderWindow&, int);
	bool isMouseOverPoint(sf::RenderWindow&, int);
	void rotatePoint(sf::RenderWindow&, int, int);
	void menuAction(sf::RenderWindow&, int);
	void bfs();
	bool checkTerms() const;
	void calculateNeighbors();
	void drawObjects(sf::RenderWindow&) const;
	void run(sf::RenderWindow&);
	void handleLevelUp(sf::RenderWindow&, int&);
	void gameOver(sf::RenderWindow&);
	std::vector<std::unique_ptr<Point>> m_points;
	Board m_board;

	sf::Music m_song;
	Menu m_menu;
};