#pragma once

#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//static Level is a level manage for the proper level loading

static class Level {
public:
	static void init();
private:
	//character representation of rooms 
	static std::vector<int**> _levels;
};

