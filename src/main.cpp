#include <iostream>
#include <fstream>
#include "Controller.h"

std::ofstream outfile ("log.txt");

int main() try
{
    Controller game;
    game.startGame();
    return EXIT_SUCCESS;
}

catch (std::exception& e)
{
    std::cout << e.what() << std::endl;
    outfile << e.what() << std::endl;
	outfile.close();
    exit(EXIT_FAILURE);
}

catch (...)
{
    outfile << "Unknown reason failure\n" << std::endl;
	outfile.close();
    exit(EXIT_FAILURE);
}
