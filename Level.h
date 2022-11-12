#pragma once

#include "Resource.h"
#include "Console.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

//static Level is a level manage for the proper level loading

static class Level {
public:
	static void init();
	//Load a level given the index
	static void load(int level);
	static sf::VertexArray level() { return _activeLevel; }
private:
	//character representation of rooms 
	static std::vector<std::vector<std::vector<int>>> _levels;
	static sf::VertexArray _activeLevel;
};

