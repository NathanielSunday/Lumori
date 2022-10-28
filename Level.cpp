#include "Level.h"


void Level::init() {
	loaded_ = 

	//input for level data file, may move this to Resource manager at some point
	std::ifstream input;
	input.open(ASSET_PATH "level.data");
	try {
		while (true) {
			int i = input.get();
			if (i == (int)'#')
				continue;

			

		}
	}
	catch (std::exception e) {
		std::cout << "Levels loaded.";
	}
}
