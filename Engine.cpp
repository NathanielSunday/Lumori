#include "Engine.h"


void Engine::run() {
	initEngine();
	initWindow();
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
	_window.create(sf::VideoMode(800, 800), "Lumori");
	_window.setFramerateLimit(60);
}

void Engine::initViewport() {

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
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}