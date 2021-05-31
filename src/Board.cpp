#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Point.h"
#include <sstream>
#include <string>
#include "Utilities.h"

void Board::readBoardFromFile(std::string fileName, std::vector<std::unique_ptr<Point>> &points)
{
	std::ifstream infile(fileName); //reading file
	
	if (infile.is_open())
	{
		std::string line;

		while (std::getline(infile, line))
		{
			std::vector<short> edges;
			std::vector<std::string> temp_line;
			std::istringstream sen(line);
			float fx, fy;

			for (std::string curr; sen >> curr;) //copy the line to string vector
				temp_line.push_back(curr);

			checkInput(temp_line); //check if the line is ok

			if (!temp_line.size()) //if its empty line
				continue;

			std::stringstream temp(temp_line[0]);
			std::stringstream temp1(temp_line[1]);
			temp >> fx;
			temp1 >> fy;

			auto checkPosition = [](float a) { return (a > Utilities::WINDOW_SIZE || a < 0); };

			if (checkPosition(fx) || checkPosition(fy))
				throw std::out_of_range("The position of the point is wrong\n");

			for (int i = 2; i < temp_line.size(); i++) //checking number of angles
			{
				short g;
				std::stringstream temp2(temp_line[i]);
				temp2 >> g;
				if(g < 1|| g > 6)
					throw std::out_of_range("The angles must be between 1-6\n");
				edges.push_back(g);
			}

			Point p(fx, fy, edges);
			points.push_back(std::make_unique<Point>(p));
		}
		infile.close();
	}
	else
		throw std::exception("Cannot open file\n");
}

void Board::checkInput(std::vector<std::string> input) const //checking input validaty
{
	for (auto i = 0; i < input.size(); i++)
	{
		if(input.size() < 3)
			throw std::exception("Too few arguments in line\n");

		if(input.size() > 8)
			throw std::exception("Too many arguments in line\n");

		if (!(std::all_of(input[i].begin(), input[i].end(), ::isdigit)))
			throw std::exception("The file can't contains any letters\n");
	}
}