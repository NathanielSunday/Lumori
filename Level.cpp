#include "Level.h"

std::vector<std::vector<std::vector<int>>> Level::_levels;
sf::VertexArray Level::_activeLevel;

void Level::init() {
	_activeLevel.setPrimitiveType(sf::Quads);
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

			_levels.push_back(std::vector<std::vector<int>>(x, std::vector<int>(y, 0)));

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
	std::cout << "\nThe levels are loaded, " << _levels[0][1][1] << std::endl;
}

void Level::load(int level) {
	//get the length of the array(s)
	int x = _levels[level].size();
	int y = _levels[level][0].size();
	std::cout << x << "," << y << std::endl;

	_activeLevel.resize(x * y * NODE_SIZE * NODE_SIZE * 4);
	for (int b = 0; b < x; ++b) {
		for (int a = 0; a < y; ++a) {
			std::cout << a << "," << b << "," << _levels[level][a][b] << std::endl;

			sf::Image image;
			//check if the node exists
			if (_levels[level][a][b] != -1)
				image.loadFromFile(ASSET_PATH NODE_PATH "map" + std::to_string(_levels[level][a][b]) + ".bmp");
			else
				image.create(NODE_SIZE, NODE_SIZE);
			
			
			
			

			//initialize our actual verticies
			for (int j = 0; j < NODE_SIZE; ++j) {
				for (int i = 0; i < NODE_SIZE; ++i) {
					int t = image.getPixel(i, j).r;

					std::cout << t << ",";
					for (int v = 0; v < 4; ++v) {
						_activeLevel[(b * 4 * NODE_SIZE * NODE_SIZE * NODE_SIZE) + (a * 4 * NODE_SIZE * NODE_SIZE) + (j * 4 * NODE_SIZE) + (i * 4) + v].position = sf::Vector2f(
							((a * NODE_SIZE) + i + (v % 3 > 0 ? 1 : 0)) * TILE_SIZE,
							((b * NODE_SIZE) + j + (v > 1 ? 1 : 0)) * TILE_SIZE
						);


						_activeLevel[(b * 4 * NODE_SIZE * NODE_SIZE * NODE_SIZE) + (a * 4 * NODE_SIZE * NODE_SIZE) + (j * 4 * NODE_SIZE) + (i * 4) + v].texCoords = sf::Vector2f(
							(t % TILEMAP_WIDTH) * TILE_SIZE,
							(t / TILEMAP_WIDTH) * TILE_SIZE
						);
					}
				}
				std::cout << std::endl;
			}
		}
	}
}