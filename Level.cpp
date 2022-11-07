#include "Level.h"

std::vector<int**> Level::_levels;
sf::VertexArray Level::_activeLevel;

void Level::init() {
	Level::_activeLevel.setPrimitiveType(sf::Quads);
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

			int** push = new int* [y];
			for (int i = 0; i < x; ++i)
				push[i] = new int[x];

			Level::_levels.push_back(push);
			continue;
		}

		for (a = 0; a < x; ++a) {
			Level::_levels[level][a][b] = std::stoi(line.substr(0, line.find(',')));
			std::cout << Level::_levels[level][a][b] << ", ";
			line.erase(0, line.find(',') + 1);
		}
		std::cout << std::endl;
		++b;
	}
	std::cout << "\nThe levels are loaded, " << Level::_levels[0][1][2] << std::endl;
}

void Level::load(int level) {
	//get the length of the array(s)
	int y = *(&Level::_levels[level] + 1) - Level::_levels[level];
	int x = *(&Level::_levels[level][0] + 1) - Level::_levels[level][0];
	Level::_activeLevel.resize(x * y * NODE_SIZE * NODE_SIZE * 4);
	for (int b = 0; b < y; ++b) {
		for (int a = 0; a < x; ++a) {
			sf::Image image;
			if (Level::_levels[level][a][b] != -1) {
				image.loadFromFile(NODE_PATH "map" + std::to_string(Level::_levels[level][a][b]) + ".bmp");
			}
			else {
				image.create(NODE_SIZE, NODE_SIZE, sf::Color::Black);
			}
			for (int j = 0; j < NODE_SIZE; ++j) {
				for (int i = 0; i < NODE_SIZE; ++i) {
					
				}
			}
		}
	}
}