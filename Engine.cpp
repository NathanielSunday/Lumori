#include "Engine.h"


void Engine::run() {
	initEngine();
	initWindow();
	mainLoop();
	cleanup();
}

State Engine::state() {
	return state_;
}

float Engine::deltaTime() {
	return deltaTime_.getElapsedTime().asSeconds();
}

void Engine::initEngine() {
	Level::init();
	state_ = State::INTRO;
}

void Engine::initWindow() {
	window_.create(sf::VideoMode(200, 200), "Lumori");
	window_.setFramerateLimit(60);
}

void Engine::mainLoop() {
	sf::Event event;
	sf::Sprite sprite;
	sprite.setTexture(*ResourceManager::get_texture("Sprite Maps/tilesheet.png"));
	while (window_.isOpen()) {
		deltaTime_.restart();
		while (window_.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window_.close();
				break;
			default:
				break;
			}
		}
		window_.clear();
		window_.draw(sprite);
		window_.display();
	}

}

void Engine::cleanup() {
	ResourceManager::flush_all();
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