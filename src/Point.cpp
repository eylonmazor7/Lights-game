#include "Point.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utilities.h"

Point::Point(float x, float y, std::vector<short>angles)
{
	m_circle.setRadius(Utilities::RADIUS);
	m_circle.setPosition(x, y);
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	
	if (x == y) //the center
	{
		m_circle.setFillColor(sf::Color::Yellow);
		m_visited = true;
	}

	for (int i = 0; i < angles.size() ; i++) //add edges
	{
		sf::RectangleShape rec(sf::Vector2f(Utilities::WIDTH, Utilities::HEIGHT));
		rec.setFillColor(sf::Color::Cyan);
		rec.setPosition(x,y);
		auto angleFunc = [](auto a) {return a * Utilities::ANGLE - 30; }; //lambda
		rec.rotate(angleFunc(angles[i]));
		rec.setOrigin((rec.getSize().x / 2), -m_circle.getRadius());
		m_edges.push_back(rec);
	} 
}

void Point::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_edges.size(); i++)
		window.draw(m_edges[i]);
	window.draw(m_circle);
}

void Point::makeNeighbors(Point* p)
{
	m_neighbors.push_back(p);
}

sf::Vector2f Point::getPosition() const
{
	return m_circle.getPosition();
}

void Point::setVisited(bool b)
{
	m_visited = b;
}

bool Point::getVisited() const
{
	return m_visited;
}

void Point::rotate(int direction)
{
	for (int i = 0; i < m_edges.size(); i++)
		m_edges[i].rotate(direction * Utilities::ANGLE);
}

std::vector<Point*>& Point::getNeighbors()
{
	return m_neighbors;
}

std::vector<sf::RectangleShape>& Point::getEdges()
{
	return m_edges;
}

void Point::light(sf::Color a)
{
	m_circle.setFillColor(a);
}
