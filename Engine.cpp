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
	return _deltaTime.asSeconds();
}

void Engine::initEngine() {
	_state = State::INTRO;
	Level::init();
}

void Engine::initWindow() {
	//, sf::Style::Titlebar | sf::Style::Close
	_window.create(sf::VideoMode(800, 700), "Lumori");
	_window.setFramerateLimit(60);
	_window.setVerticalSyncEnabled(true);
}

void Engine::initViewport() {
	_viewport.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(TILE_SIZE * 16, TILE_SIZE * 14)));


	sf::Vector2u window = _window.getSize();
	//1x wide if taller window, 1x tall if wider window
	sf::Vector2f ratio(
		(window.y / 7.0f) >= (window.x / 8.0f) ? 1.0f : (window.y / 7.0f) / (window.x / 8.0f),
		(window.x / 8.0f) >= (window.y / 7.0f) ? 1.0f : (window.x / 8.0f) / (window.y / 7.0f)
	);
	Console::Debug("Ratio: " + std::to_string(ratio.x) + ", " + std::to_string(ratio.y));
	//should be moved half of what space would be
	sf::Vector2f center(
		(window.y / 7.0f) >= (window.x / 8.0f) ? 0.0f : (1.0f - ratio.x) / 2.0f,
		(window.x / 8.0f) >= (window.y / 7.0f) ? 0.0f : (1.0f - ratio.y) / 2.0f
	);
	Console::Debug("Corner Pos: " + std::to_string(center.x) + ", " + std::to_string(center.y));

	sf::FloatRect viewSize(center, ratio);
	_viewport.setViewport(viewSize);
	_window.setView(_viewport);

}

void Engine::mainLoop() {
	sf::Event event;
	sf::Sprite sprite;
	sf::Keyboard keyboard;
	sprite.setTexture(*Resource::get_texture(TILE_PATH "tilesheet.png"));
	Level::load(0);
	while (_window.isOpen()) {
		_deltaTime = _deltaClock.restart();
		while (_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::Resized:
				initViewport();
				break;
			default:
				break;
			}
		}
		//should probably write to a render texture and draw that texture to window instead of directly to window

		if (keyboard.isKeyPressed(sf::Keyboard::A))  _viewport.move(-10.0f * TILE_SIZE * deltaTime(), 0);
		if (keyboard.isKeyPressed(sf::Keyboard::D)) _viewport.move(10.0f * TILE_SIZE * deltaTime(), 0);
		if (keyboard.isKeyPressed(sf::Keyboard::W))    _viewport.move(0, -10.0f * TILE_SIZE * deltaTime());
		if (keyboard.isKeyPressed(sf::Keyboard::S))  _viewport.move(0, 10.0f * TILE_SIZE * deltaTime());
		_window.clear();
		_window.setView(_viewport);
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