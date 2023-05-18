#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <unordered_map>
#include <memory>

#define TILE_SIZE		16
#define TEXTURE_SIZE	16
#define NODE_SIZE		16
#define TILEMAP_WIDTH	6
#define ASSET_PATH		"Assets/"
#define NODE_PATH		"level/"
#define SPRITE_PATH		"sprite/entity/"
#define TILE_PATH		"sprite/tile/"

enum TILE {
	GRASS,			//tile 00
	SAND,			//tile 01
	WATER_SHALLOW,	//tile 02
	WATER_DEEP,		//tile 03
};

static class Resource {
public:
	//get a texture from a specified path
	static std::shared_ptr<sf::Texture> GetTexture(const std::string& file);
	//get a sound from a specified path
	static std::shared_ptr<sf::Sound> GetSound(const std::string& file);
	//get music from a specified path
	static std::shared_ptr<sf::Music> GetMusic(const std::string& file);
	//clear unused loaded assets
	static void FlushAll();
	//clear unused loaded textures
	static void FlushTextures();
	//clear unused loaded sounds
	static void FlushSounds();
	//clear unused loaded music
	static void FlushMusic();

private:
	//flush a templated pointer map
	template <typename T>
	static void Flush(std::unordered_map<std::string, std::shared_ptr<T>>& map);
	//a dynamically allocated list of all called upon Textures.
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	//a dynamically allocated list of all called upon Sounds.
	static std::unordered_map<std::string, std::shared_ptr<sf::Sound>> m_sounds;
	//a dynamically allocated list of all called upon Music.
	static std::unordered_map<std::string, std::shared_ptr<sf::Music>> m_music;
};

