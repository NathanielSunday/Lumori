#pragma once

#include <SFML\Graphics.hpp>

//static Level is a level manage for the proper level loading

static class Level {
public:
	static void Initialize();
	//Load a level given the index
	static void Load(int level);
	static sf::VertexArray Get() { return _activeLevel; }
private:
	//use this to draw to
	sf::RenderTexture _texture;
	//character representation of rooms 
	static std::vector<std::vector<std::vector<int>>> _levels;
	static sf::VertexArray _activeLevel;
};

