#pragma once

//#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
//static Level is a level manage for the proper level loading

static class Level {
public:
	static void Initialize();
	//Load a level given the index
	static void Load(int level);
	static sf::VertexArray Get() { return m_activeLevel; }
private:
	//use this to draw to
	sf::RenderTexture m_texture;
	//character representation of rooms 
	static std::vector<std::vector<std::vector<int>>> m_levels;
	static sf::VertexArray m_activeLevel;
};

