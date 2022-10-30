#pragma once

#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//static Level is a level manage for the proper level loading

static class Level {
public:
	static sf::Texture** textures;

	static void init();
	//Load a level given the index
	static void load(int level);
private:
	//character representation of rooms 
	static std::vector<int**> _levels;
};

