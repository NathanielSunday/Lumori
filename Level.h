#pragma once

#include "ResourceManager.h"
#include <string>
#include <fstream>

//static Level is a level manage for the proper level loading

static class Level {
public:
	static void init();
private:
	static int* loaded_;
};

