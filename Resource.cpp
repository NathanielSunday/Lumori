#include "Resource.hpp"
#include "Console.hpp"


//a dynamically allocated list of all called upon Textures.
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resource::m_textures;
//a dynamically allocated list of all called upon Sounds.
std::unordered_map<std::string, std::shared_ptr<sf::Sound>> Resource::m_sounds;
//a dynamically allocated list of all called upon Music.
std::unordered_map<std::string, std::shared_ptr<sf::Music>> Resource::m_music;


std::shared_ptr<sf::Texture> Resource::GetTexture(const std::string& file) {
	const auto i = m_textures.find(file);

	if (i != m_textures.end()) return i->second;
	else {
		auto t = std::make_shared<sf::Texture>();
		if (t->loadFromFile(ASSET_PATH + file)) m_textures.insert({ file, t });
		else Console::Error("Could not load texture at '" + file + "'");
		return t;
	}
}

std::shared_ptr<sf::Sound> Resource::GetSound(const std::string& file) {
	const auto i = m_sounds.find(file);

	if (i != m_sounds.end()) {
		return i->second;
	}
	else {
		auto t = std::make_shared<sf::Sound>();
		//t->;
		m_sounds.insert({ file, t });
		return t;
	}
}

std::shared_ptr<sf::Music> Resource::GetMusic(const std::string& file) {
	const auto i = m_music.find(file);

	if (i != m_music.end()) return i->second;
	else {
		auto t = std::make_shared<sf::Music>();
		if (t->openFromFile(ASSET_PATH + file)) m_music.insert({ file, t });
		else Console::Error("Could not load music at '" + file + "'");
		return t;
	}
}

void Resource::FlushAll() {
	FlushTextures();
	FlushSounds();
	FlushMusic();
}

void Resource::FlushTextures() { Flush(m_textures); }
void Resource::FlushSounds() { Flush(m_sounds); }
void Resource::FlushMusic() { Flush(m_music); }

template <typename T>
void Resource::Flush(std::unordered_map<std::string, std::shared_ptr<T>>& map) {
	for (auto m : map) { m.second.reset(); }
	map.clear();
}