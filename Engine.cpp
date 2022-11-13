#include "Engine.h"


void Engine::run() {
	initEngine();
	//load some sort of setting perhaps?
	initWindow();
	initViewport();
	mainLoop();
	cleanup();
}

State Engine::state() {
	return _state;
}

float Engine::deltaTime() {
	return _deltaTime.getElapsedTime().asSeconds();
}

void Engine::initEngine() {
	_state = State::INTRO;
	Level::init();
}

void Engine::initWindow() {
	_window.create(sf::VideoMode(800, 700), "Lumori", sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(60);
}

void Engine::initViewport() {

	_viewport.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(256, 224)));
	_window.setView(_viewport);
}

void Engine::mainLoop() {
	sf::Event event;
	sf::Sprite sprite;
	sprite.setTexture(*Resource::get_texture(TILE_PATH "tilesheet.png"));
	Level::load(0);
	while (_window.isOpen()) {
		_deltaTime.restart();
		while (_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				_window.close();
				break;
			default:
				break;
			}
		}

		_window.clear();
		//_window.draw(sprite);
		_window.draw(Level::level(), &*Resource::get_texture(TILE_PATH "tilesheet.png"));
		_window.display();
	}

}

void Engine::cleanup() {
	Resource::flush_all();
}

int main() {
	Engine game;

	try {
		game.run();
	}
	catch (const std::exception& e) {
		Console::Error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}