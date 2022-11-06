#include "Level.h"

sf::Texture** Level::_activeLevel;
std::vector<int**> Level::_levels;

void Level::init() {
	//input for level data file, may move this to Resource manager at some point
	std::ifstream filein(ASSET_PATH "level.data");
	int level = -1, a, b, x, y;
	for (std::string line; std::getline(filein, line); /*no global increment*/) {
		if (line.at(0) == '#') continue;
		if (line.at(0) == '!') {
			++level;
			std::cout << "Level: " << level << std::endl;
			b = 0;

			line.erase(0, 1);
			x = std::stoi(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			y = std::stoi(line.substr(0, line.find(',')));

			int** push = new int*[y];
			for (int i = 0; i < x; ++i)
				push[i] = new int[x];

			_levels.push_back(push);
			continue;
		}

		for (a = 0; a < x; ++a) {
			_levels[level][a][b] = std::stoi(line.substr(0, line.find(',')));
			std::cout << _levels[level][a][b] << ", ";
			line.erase(0, line.find(',') + 1);
		}
		std::cout << std::endl;
		++b;
	}
	std::cout << "\nThe levels are loaded, " << _levels[0][1][2] << std::endl;
}
  
void Level::load(int level) {
	//init activeLevels [level][LENGTH] here
	for (int b = 0; b < *(&_levels[level] + 1) - _levels[level]; ++b) {

		for (int a = 0; a < *(&_levels[level][b] + 1) - _levels[level][b]; ++a) {
			//init activeLevels [level][b][LENGTH] here
			
		}
	}
}