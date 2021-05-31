#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Menu.h"

class Board
{
public:
	Board() = default;
	~Board() = default;

	void readBoardFromFile(std::string, std::vector<std::unique_ptr<Point>> &points);
private:
	void checkInput(std::vector<std::string>) const;
};