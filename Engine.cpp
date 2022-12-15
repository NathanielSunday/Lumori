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

void Engine::drawToLayer(Layer layer, const sf::Drawable& drawable, const sf::RenderStates& states) {
	if (layer == Layer::FINAL) return Console::Error("Cannot write to layer 'FINAL'");
	_drawStack[layer].draw(drawable, states);
}

void Engine::initEngine() {
	_state = State::INTRO;
	Level::init();
	_drawStack = new sf::RenderTexture[Layer::FINAL + 1];
	for (int i = 0; i <= Layer::FINAL; ++i) _drawStack[i].create(800, 700);
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
	//_window.setView(_viewport);

}

void Engine::mainLoop() {
	sf::Event event;
	sf::Sprite sprite;
	sf::Keyboard keyboard;
	sprite.setTexture(*Resource::get_texture(SPRITE_PATH "player.png"));
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


		sf::Vector2f speed;

		if (keyboard.isKeyPressed(sf::Keyboard::A))	sprite.move(-5.0f * TILE_SIZE * deltaTime(), 0);
		if (keyboard.isKeyPressed(sf::Keyboard::D)) sprite.move(5.0f * TILE_SIZE * deltaTime(), 0);
		if (keyboard.isKeyPressed(sf::Keyboard::W))	sprite.move(0, -5.0f * TILE_SIZE * deltaTime());
		if (keyboard.isKeyPressed(sf::Keyboard::S))	sprite.move(0, 5.0f * TILE_SIZE * deltaTime());
		speed *= TILE_SIZE * deltaTime();

		sprite.move(speed);

		drawToLayer(Layer::BACKGROUND, Level::level(), &*Resource::get_texture(TILE_PATH "tilesheet.png"));
		//drawToLayer(Layer::MIDGROUND, sprite);

		
		_window.clear();
		render();
		_viewport.setCenter(sprite.getPosition());
		_window.draw(sprite);
		_window.setView(_viewport);
		_window.display();
		//why teh fuck does refreshing break it
		//refresh();
	}

}

void Engine::render() {
	for (int i = 0; i < Layer::FINAL; ++i) {
		_drawStack[i].display();
		_drawStack[Layer::FINAL].draw(sf::Sprite(_drawStack[i].getTexture()));
	}
	_drawStack[Layer::FINAL].display();
	_window.draw(sf::Sprite(_drawStack[Layer::FINAL].getTexture()));
	refresh();
}

void Engine::refresh() {
	for (int i = 0; i <= Layer::FINAL; ++i) {
		_drawStack[i].clear(sf::Color::Transparent);
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