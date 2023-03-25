#include "Engine.hpp"
#include "Console.hpp"
#include "Resource.hpp"
#include "Level.hpp"
#include <stdexcept>
//#include <memory>

void Engine::run() {
	initEngine();
	//load some sort of setting perhaps?
	initWindow();
	initViewport();
	mainLoop();
	cleanup();
}

State Engine::state() {
	return m_state;
}

float Engine::deltaTime() {
	return m_deltaTime.asSeconds();
}

void Engine::drawToLayer(const sf::Drawable& drawable, Layer layer, const sf::RenderStates& states) {
	if (layer == Layer::FINAL) return Console::Error("Cannot write to layer 'FINAL'");
	if (layer == Layer::ENTITY) return Console::Error("Cannot write to layer 'ENTITY' using 'drawToLayer', use 'addCollidable' instead");
	m_drawStack[layer].draw(drawable, states);
}

void Engine::addCollidable(Collidable& collidable) {
	m_collidableStack.push_back(&collidable);
}

void Engine::initEngine() {
	m_state = State::INTRO;
	Level::Initialize();
	m_drawStack = new sf::RenderTexture[Layer::FINAL + 1];
	for (int i = 0; i <= Layer::FINAL; ++i) m_drawStack[i].create(800, 700);
}

void Engine::initWindow() {
	//, sf::Style::Titlebar | sf::Style::Close
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	m_window.create(sf::VideoMode(800, 700), "Lumori", sf::Style::Default, settings);
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);
}

void Engine::initViewport() {
	m_viewport.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(TILE_SIZE * 16, TILE_SIZE * 14)));


	sf::Vector2u window = m_window.getSize();
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
	m_viewport.setViewport(viewSize);
	//_window.setView(_viewport);

}

void Engine::mainLoop() {
	sf::Event event;
	sf::Keyboard keyboard;
	Collidable player(SPRITE_PATH "player.png", sf::Vector2f(0, 0) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f);
	Collidable playernt(SPRITE_PATH "player.png", sf::Vector2f(5, 5) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f, true);
	Collidable immovable(SPRITE_PATH "player.png", sf::Vector2f(10, 5) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f, true, true);
	Collidable::SetDisplayColliders();
	Level::Load(0);
	while (m_window.isOpen()) {
		while (m_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::Resized:
				initViewport();
				break;
			default:
				break;
			}
		}
		//LOGIC
		update();


		sf::Vector2f speed(0, 0);

		if (keyboard.isKeyPressed(sf::Keyboard::A))	speed.x += -1.0f;
		if (keyboard.isKeyPressed(sf::Keyboard::D)) speed.x += 1.0f;
		if (keyboard.isKeyPressed(sf::Keyboard::W))	speed.y += -1.0f;
		if (keyboard.isKeyPressed(sf::Keyboard::S))	speed.y += 1.0f;
		if (speed.x != 0 || speed.y != 0) {
			speed /= sqrt(speed.x * speed.x + speed.y * speed.y);
			speed *= TILE_SIZE * deltaTime() * 5.0f;
			player.move(speed);

		}

		//GRAPHIC
		drawToLayer(Level::Get(), Layer::BACKGROUND, &*Resource::GetTexture(TILE_PATH "tilesheet.png"));
		addCollidable(player);
		addCollidable(playernt);
		addCollidable(immovable);

		m_window.clear();
		render();
		m_viewport.setCenter(player.getPosition());
		m_window.setView(m_viewport);
		m_window.display();
	}
}

void Engine::update() {
	m_deltaTime = m_deltaClock.restart();
	Collidable::CheckGlobalCollision();
	Console::Info(std::to_string(1 / deltaTime()));
}

void Engine::render() {

	for (int i = 0; i < Layer::FINAL; ++i) {
		if (i == Layer::ENTITY) {
			//sf::Vector2f pos = m_collidableStack.at(0)->getPosition();
			std::sort(m_collidableStack.begin(), m_collidableStack.end(), Collidable::zIndex);
			for (int j = 0; j < m_collidableStack.size(); ++j) m_window.draw(*m_collidableStack.at(j));
			continue;
		}
		m_drawStack[i].display();
		m_window.draw(sf::Sprite(m_drawStack[i].getTexture()));
		//_drawStack[Layer::FINAL].draw(sf::Sprite(_drawStack[i].getTexture()));
	}
	//_drawStack[Layer::FINAL].display();
	m_window.draw(sf::Sprite(m_drawStack[Layer::FINAL].getTexture()));
	refresh();
}

void Engine::refresh() {
	for (int i = 0; i <= Layer::FINAL; ++i) {
		m_drawStack[i].clear(sf::Color::Transparent);
	}
	m_collidableStack.clear();
}

void Engine::cleanup() {
	Resource::FlushAll();
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