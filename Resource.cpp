#include "Resource.h"


//a dynamically allocated list of all called upon Textures.
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resource::_textures;
//a dynamically allocated list of all called upon Sounds.
std::unordered_map<std::string, std::shared_ptr<sf::Sound>> Resource::_sounds;
//a dynamically allocated list of all called upon Music.
std::unordered_map<std::string, std::shared_ptr<sf::Music>> Resource::_music;


std::shared_ptr<sf::Texture> Resource::GetTexture(const std::string& file) {
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

std::shared_ptr<sf::Sound> Resource::GetSound(const std::string& file) {
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

std::shared_ptr<sf::Music> Resource::GetMusic(const std::string& file) {
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

void Resource::FlushAll() {
	FlushTextures();
	FlushSounds();
	FlushMusic();
}

void Resource::FlushTextures() { Flush(_textures); }
void Resource::FlushSounds() { Flush(_sounds); }
void Resource::FlushMusic() { Flush(_music); }

//get a texture from a specified path
template <typename T>
void Resource::Flush(std::unordered_map<std::string, std::shared_ptr<T>>& map) {
	for (auto m : map) { m.second.reset(); }
	map.clear();
}