#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Utilities.h"
#include <vector>
#include <queue>
#include <Windows.h> //for Sleep

void Controller::startGame()
{
	auto window = sf::RenderWindow(sf::VideoMode(Utilities::WINDOW_SIZE, Utilities::WINDOW_SIZE), "Lights Game - Dor and Eylon", sf::Style::Close);
	m_song.openFromFile("song.ogg");
	m_song.play();
	
	startGameMenu(window);	
}

void Controller::run(sf::RenderWindow& window)
{
	calculateNeighbors();

	while (window.isOpen()) //level event loop
	{
		window.clear();
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				for (auto i = 0; i != m_points.size(); i++)
					if (isMouseOverPoint(window, i))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							rotatePoint(window, i, 1);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
							rotatePoint(window, i, -1);
					}
							
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		bfs();
		drawObjects(window);
		window.display();
		if (checkTerms())
		{
			Sleep(800);
			m_points.clear();
			return;
		}
	}
}

void Controller::drawObjects(sf::RenderWindow& window) const
{
	for (auto i = 0; i != m_points.size(); i++)
		m_points[i]->draw(window);
}

void Controller::startGameMenu(sf::RenderWindow& window) //main menu
{
	while (window.isOpen())
	{
		window.clear();
		m_menu.drawMenu(window);
		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				for (int i = 1; i < Utilities::ICONS; i++)
					if (isMouseOverIcon(window, i))
						menuAction(window, i);
				break;

			case sf::Event::Closed:
				window.close();
			}
		}
	}
}

bool Controller::isMouseOverIcon(sf::RenderWindow & window, int index) //level pressed
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(Utilities::ICON_SIZE, Utilities::ICON_SIZE));
	shape.setPosition(90 * index, 350);
	
	auto shapePos = shape.getGlobalBounds();
	
	if (shapePos.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		return true;
	return false;
}

void Controller::calculateNeighbors()
{
	for (auto first = 0; first != m_points.size(); first++)
	{
		auto fPos = m_points[first]->getPosition();
		for (auto second = 0; second != m_points.size(); second++)
		{
			auto sPos = m_points[second]->getPosition();

			if (fPos.y == sPos.y && abs(fPos.x - sPos.x) == Utilities::DISTANCE) // same row
				m_points[first]->makeNeighbors(m_points[second].get());

			else if(abs(fPos.y - sPos.y) == Utilities::HEIGHT_DISTANCE && abs(fPos.x - sPos.x) == Utilities::DISTANCE/2) //close col
				m_points[first]->makeNeighbors(m_points[second].get());
		}
		if (m_points[first]->getNeighbors().size() < m_points[first]->getEdges().size())
			throw std::exception("Too many edges for a single vertex\n");
	}
}

void Controller::menuAction(sf::RenderWindow& window, int index)
{
	while (true) {
		switch (index)
		{
		case 1:
			m_board.readBoardFromFile("level1.txt", m_points);
			break;
		case 2:
			m_board.readBoardFromFile("level2.txt", m_points);
			break;
		case 3:
			m_board.readBoardFromFile("level3.txt", m_points);
			break;
		case 4:
			window.close();
			return;
			break;
		}
		run(window);
		if (++index == 4) {
			m_menu.drawGameOver(window);
			//window.clear();
			return;
		}
		else
			m_menu.drawLevelUp(window);
	}
	
}

void Controller::bfs()
{
	std::queue<Point*> bfs_queue;

	for (auto i = 0; i != m_points.size(); i++)
	{
		if (m_points[i]->getPosition() == (sf::Vector2f(250, 250)))
		{
			bfs_queue.push(m_points[i].get()); //add the center to be source for BFS
			m_points[i]->setVisited(true);
		}
		else
		{
			m_points[i]->setVisited(false);
			m_points[i]->light(sf::Color::Red);
		}
	}

	auto BFS = bfs_queue.front();
	
	while(!bfs_queue.empty())
	{
		BFS = bfs_queue.front();
		//loops to check all the shcenim and add to queue if intesect is true
		for (int i = 0; i < BFS->getEdges().size(); i++) //any edge in curr vertex
		{
			bool continueSearech = true;
			for (int j = 0; continueSearech && j < BFS->getNeighbors().size() ; j++)//any shachen, if is not visited already
			{
				if (BFS->getNeighbors()[j]->getVisited()) //already in queue
					continue;

				for (int k = 0; continueSearech && k < BFS->getNeighbors()[j]->getEdges().size() ; k++)//any edge in the shachen
				{
					auto aPos = BFS->getEdges()[i].getGlobalBounds();
					auto bPos = BFS->getNeighbors()[j]->getEdges()[k].getGlobalBounds();
					auto glambda = [](auto a, auto b) { return a.intersects(b);  };
					if (glambda(aPos,bPos))
					{
						bfs_queue.push(BFS->getNeighbors()[j]);
						BFS->getNeighbors()[j]->light(sf::Color::Yellow);
						BFS->getNeighbors()[j]->setVisited(true);
						continueSearech = false;
					}
				}
			}
		}
		bfs_queue.pop();
	}
}

bool Controller::isMouseOverPoint(sf::RenderWindow& window, int index)
{
	sf::CircleShape shape;
	shape.setRadius(Utilities::RADIUS);
	shape.setPosition(sf::Vector2f(m_points[index]->getPosition().x - Utilities::RADIUS,
		m_points[index]->getPosition().y - Utilities::RADIUS));

	auto shapePos = shape.getGlobalBounds();
	
	if (shapePos.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		return true;
	return false;
}

void Controller::rotatePoint(sf::RenderWindow& window, int index, int direction)
{
	m_points[index]->rotate(direction);
}

bool Controller::checkTerms() const
{
	for (auto i = 0; i != m_points.size(); i++)
		if (!m_points[i]->getVisited())
			return false;
	return true;
}

void Controller::gameOver(sf::RenderWindow& window)
{

}