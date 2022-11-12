#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>


#define TILE_SIZE		16
#define TEXTURE_SIZE	16
#define NODE_SIZE		20
#define TILEMAP_WIDTH	6
#define ASSET_PATH		"Assets/"
#define NODE_PATH		"level/"
#define SPRITE_PATH		"sprite/entity/"
#define TILE_PATH		"sprite/tile/"



/*////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*\
|															 |
|			Do the shit properly:							 |
|						keep resources managed internally,	 |
|						make calls to this class return		 |
|						objects/sprites/music				 |
|															 |
\*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////////*/


enum TILE {
	GRASS,

};




static class Resource {
public:
	//get a texture from a specified path
	static std::shared_ptr<sf::Texture> get_texture(const std::string& file);
	//get a sound from a specified path
	static std::shared_ptr<sf::Sound> get_sound(const std::string& file);
	//get music from a specified path
	static std::shared_ptr<sf::Music> get_music(const std::string& file);
	//destroy all loaded assets
	static void flush_all();
	//destroy all loaded textures
	static void flush_textures();
	//destroy all loaded sounds
	static void flush_sounds();
	//destroy all loaded music
	static void flush_music();

private:
	//get a texture from a specified path
	template <typename T>
	static void flush(std::unordered_map<std::string, std::shared_ptr<T>>& map);
	//a dynamically allocated list of all called upon Textures.
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
	//a dynamically allocated list of all called upon Sounds.
	static std::unordered_map<std::string, std::shared_ptr<sf::Sound>> _sounds;
	//a dynamically allocated list of all called upon Music.
	static std::unordered_map<std::string, std::shared_ptr<sf::Music>> _music;
};

