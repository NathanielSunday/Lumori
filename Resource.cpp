#include "Resource.h"


//a dynamically allocated list of all called upon Textures.
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resource::textures_;
//a dynamically allocated list of all called upon Sounds.
std::unordered_map<std::string, std::shared_ptr<sf::Sound>> Resource::sounds_;
//a dynamically allocated list of all called upon Music.
std::unordered_map<std::string, std::shared_ptr<sf::Music>> Resource::music_;


std::shared_ptr<sf::Texture> Resource::get_texture(const std::string& file) {
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

std::shared_ptr<sf::Sound> Resource::get_sound(const std::string& file) {
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

std::shared_ptr<sf::Music> Resource::get_music(const std::string& file) {
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

void Resource::flush_all() {
	flush_textures();
	flush_sounds();
	flush_music();
}

void Resource::flush_textures() { flush(textures_); }
void Resource::flush_sounds() { flush(sounds_); }
void Resource::flush_music() { flush(music_); }

//get a texture from a specified path
template <typename T>
void Resource::flush(std::unordered_map<std::string, std::shared_ptr<T>>& map) {
	for (auto m : map) { m.second.reset(); }
	map.clear();
}