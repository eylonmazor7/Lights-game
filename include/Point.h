#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Point
{
public:
	Point(float x, float y, std::vector<short> angles);
	~Point() = default;

	void rotate(int);
	void makeNeighbors(Point*);
	void draw(sf::RenderWindow&) const;
	void setVisited(bool);
	void light(sf::Color);
	bool getVisited() const;
	
	std::vector<Point*>& getNeighbors();
	std::vector<sf::RectangleShape>& getEdges();
	sf::Vector2f getPosition() const;
	
private:
	std::vector<sf::RectangleShape> m_edges; //the rectangle, the angle (between 1-6 * 60 - 30)
	std::vector<Point*> m_neighbors;
	sf::CircleShape m_circle;
	bool m_visited = false;
};