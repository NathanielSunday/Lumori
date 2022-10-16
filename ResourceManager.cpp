#include "ResourceManager.h"


//a dynamically allocated list of all called upon Textures.
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> ResourceManager::textures_;
//a dynamically allocated list of all called upon Sounds.
std::unordered_map<std::string, std::shared_ptr<sf::Sound>> ResourceManager::sounds_;
//a dynamically allocated list of all called upon Music.
std::unordered_map<std::string, std::shared_ptr<sf::Music>> ResourceManager::music_;


std::shared_ptr<sf::Texture> ResourceManager::get_texture(const std::string& file) {
	const auto i = textures_.find(file);

	if (i != textures_.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Texture>();
		t->loadFromFile(ASSET_PATH + file);
		textures_.insert({ file, t });
		return t;
	}
}

std::shared_ptr<sf::Sound> ResourceManager::get_sound(const std::string& file) {
	const auto i = sounds_.find(file);

	if (i != sounds_.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Sound>();
		//t->;
		sounds_.insert({ file, t });
		return t;
	}
}

std::shared_ptr<sf::Music> ResourceManager::get_music(const std::string& file) {
	const auto i = music_.find(file);

	if (i != music_.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Music>();
		t->openFromFile(ASSET_PATH + file);
		music_.insert({ file, t });
		return t;
	}
}

void ResourceManager::flush_all() {
	flush_textures();
	flush_sounds();
	flush_music();
}

void ResourceManager::flush_textures() { flush(textures_); }
void ResourceManager::flush_sounds() { flush(sounds_); }
void ResourceManager::flush_music() { flush(music_); }

//get a texture from a specified path
template <typename T>
void ResourceManager::flush(std::unordered_map<std::string, std::shared_ptr<T>>& map) {
	for (auto m : map) { m.second.reset(); }
	map.clear();
}