#include "Resource.h"


//a dynamically allocated list of all called upon Textures.
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resource::_textures;
//a dynamically allocated list of all called upon Sounds.
std::unordered_map<std::string, std::shared_ptr<sf::Sound>> Resource::_sounds;
//a dynamically allocated list of all called upon Music.
std::unordered_map<std::string, std::shared_ptr<sf::Music>> Resource::_music;


std::shared_ptr<sf::Texture> Resource::get_texture(const std::string& file) {
	const auto i = _textures.find(file);

	if (i != _textures.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Texture>();
		t->loadFromFile(ASSET_PATH + file);
		_textures.insert({ file, t });
		return t;
	}
}

std::shared_ptr<sf::Sound> Resource::get_sound(const std::string& file) {
	const auto i = _sounds.find(file);

	if (i != _sounds.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Sound>();
		//t->;
		_sounds.insert({ file, t });
		return t;
	}
}

std::shared_ptr<sf::Music> Resource::get_music(const std::string& file) {
	const auto i = _music.find(file);

	if (i != _music.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Music>();
		t->openFromFile(ASSET_PATH + file);
		_music.insert({ file, t });
		return t;
	}
}

void Resource::flush_all() {
	flush_textures();
	flush_sounds();
	flush_music();
}

void Resource::flush_textures() { flush(_textures); }
void Resource::flush_sounds() { flush(_sounds); }
void Resource::flush_music() { flush(_music); }

//get a texture from a specified path
template <typename T>
void Resource::flush(std::unordered_map<std::string, std::shared_ptr<T>>& map) {
	for (auto m : map) { m.second.reset(); }
	map.clear();
}