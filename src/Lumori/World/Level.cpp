#include <Lumori/World/Level.hpp>
#include <Lumori/Engine/Resource.hpp>
#include <Lumori/Engine/Console.hpp>

#include <fstream>

std::vector<std::vector<std::vector<int>>> Level::m_levels;
sf::VertexArray Level::m_activeLevel;

void Level::Initialize() {
	m_activeLevel.setPrimitiveType(sf::Quads);
	//input for level data file, may move this to Resource manager at some point
	std::ifstream filein(ASSET_PATH "level.data");
	int level = -1, a, b, x, y;
	for (std::string line; std::getline(filein, line); /*no global increment*/) {
		if (line.at(0) == '#') continue;
		if (line.at(0) == '!') {
			++level;
			b = 0;

			line.erase(0, 1);
			x = std::stoi(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			y = std::stoi(line.substr(0, line.find(',')));

			m_levels.push_back(std::vector<std::vector<int>>(x, std::vector<int>(y, 0)));

			continue;
		}

		for (a = 0; a < x; ++a) {
			m_levels[level][a][b] = std::stoi(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
		}
		++b;
	}
	Console::Info("All primitive levels have been loaded!");
}

void Level::Load(int level) {
	//get the length of the array(s)
	int x = m_levels[level].size();
	int y = m_levels[level][0].size();



	m_activeLevel.resize(x * y * NODE_SIZE * NODE_SIZE * 4);
	for (int b = 0; b < y; ++b) {
		for (int a = 0; a < x; ++a) {
			sf::Image image;

			//check if the node exists
			if (m_levels[level][a][b] != -1) {
				if (!image.loadFromFile(ASSET_PATH NODE_PATH "map" + std::to_string(m_levels[level][a][b]) + ".png")) {
					Console::Error("Failed to load level. The file \"map" + std::to_string(m_levels[level][a][b]) + ".png\" is missing or corrupt.");
					return;
				}
			}
			else
				image.create(NODE_SIZE, NODE_SIZE);




			//initialize our actual verticies
			for (int j = 0; j < NODE_SIZE; ++j) {
				for (int i = 0; i < NODE_SIZE; ++i) {
					int t = image.getPixel(i, j).r - 1;
					if (t != -1) {
						for (int v = 0; v < 4; ++v) {
							//top left, top right, bottom right, bottom left

							//uh... I don't know how to comment this properly, but loop math

							//b * x * node * node * 4
							//a * node * node * 4
							//j * node * 4
							//i * 4

							int c = 4 * (NODE_SIZE * (NODE_SIZE * ((b * x) + a) + j) + i) + v;

							m_activeLevel[c].position = sf::Vector2f(
								(((a * NODE_SIZE) + i + (v % 3 > 0 ? 1 : 0)) * TILE_SIZE),
								(((b * NODE_SIZE) + j + (v > 1 ? 1 : 0)) * TILE_SIZE)
							);

							m_activeLevel[c].texCoords = sf::Vector2f(
								(((t % TILEMAP_WIDTH) + (v % 3 > 0 ? 1 : 0)) * TEXTURE_SIZE),
								(((t / TILEMAP_WIDTH) + (v > 1 ? 1 : 0)) * TEXTURE_SIZE)
							);
						}
					}
				}
			}
		}
	}
	Console::Info("Level " + std::to_string(level) + " loaded onto VRAM.");
}
