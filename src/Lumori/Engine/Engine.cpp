#include <Lumori/Engine/Engine.hpp>
#include <Lumori/Engine/Console.hpp>
#include <Lumori/Engine/Resource.hpp>
#include <Lumori/World/Level.hpp>
#include <Lumori/Interaction/Entity.hpp>
#include <SFML/Window/Event.hpp>

std::unique_ptr<Engine> Engine::Instance;

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
	m_drawStack[layer]->draw(drawable, states);
}

void Engine::addEntity(Entity& entity) {
	m_entityStack.push_back(&entity);
}

void Engine::initEngine() {
	Instance = std::unique_ptr<Engine>(this);
	m_state = State::PLAY;
	Level::Initialize();

	for (int i = 0; i <= Layer::FINAL; ++i) {
		sf::RenderTexture* texture;
		texture = new sf::RenderTexture();
		texture->create(800, 700);
		m_drawStack.push_back(texture);
	}
}

void Engine::initWindow() {
	//, sf::Style::Titlebar | sf::Style::Close
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	m_window.create(sf::VideoMode(800, 700), "Lumori", sf::Style::Default, settings);
	bool vsync = true;
	int framerate = 60;
	m_window.setVerticalSyncEnabled(vsync);
	m_window.setFramerateLimit(0);
	if(!vsync) m_window.setFramerateLimit(framerate);
}

void Engine::initViewport() {
	sf::Vector2f aspect(16, 9);

	m_viewport.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(TILE_SIZE * aspect.x, TILE_SIZE * aspect.y)));

	sf::Vector2u window = m_window.getSize();
	//1x wide if taller window, 1x tall if wider window
	sf::Vector2f ratio(
		(window.y / aspect.y) >= (window.x / aspect.x) ? 1.0f : (window.y / aspect.y) / (window.x / aspect.x),
		(window.x / aspect.x) >= (window.y / aspect.y) ? 1.0f : (window.x / aspect.x) / (window.y / aspect.y)
	);
	Console::Debug("Ratio: " + std::to_string(ratio.x) + ", " + std::to_string(ratio.y));
	//should be moved half of what space would be
	sf::Vector2f center(
		(window.y / aspect.y) >= (window.x / aspect.x) ? 0.0f : (1.0f - ratio.x) / 2.0f,
		(window.x / aspect.x) >= (window.y / aspect.y) ? 0.0f : (1.0f - ratio.y) / 2.0f
	);
	Console::Debug("Corner Pos: " + std::to_string(center.x) + ", " + std::to_string(center.y));

	sf::FloatRect viewSize(center, ratio);
	m_viewport.setViewport(viewSize);
	//_window.setView(_viewport);
}

void Engine::mainLoop() {
	sf::Event event;
	Entity player(SPRITE_PATH "player.png", sf::Vector2f(0, 0) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f);
	Entity playernt(SPRITE_PATH "player.png", sf::Vector2f(5, 5) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f, true);
	Entity immovable(SPRITE_PATH "player.png", sf::Vector2f(10, 5) * 16.0f, sf::Vector2f(0.5, 0.5) * 16.0f, sf::Vector2f(0.25, 0.5) * 16.0f, true, true);
	Entity::SetDisplayColliders(true);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	speed.x += -1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	speed.x += 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	speed.y += -1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	speed.y += 1.0f;
		if (speed.x != 0 || speed.y != 0) {
			speed /= sqrt(speed.x * speed.x + speed.y * speed.y);
			speed *= TILE_SIZE * deltaTime() * 5.0f;
			player.move(speed);

		}

		//GRAPHIC

		//it may be a good idea to make an instance of Level instead of making everything static
		drawToLayer(Level::Get(), Layer::BACKGROUND, &*Resource::GetTexture(TILE_PATH "tilesheet.png"));
		addEntity(player);
		addEntity(playernt);
		addEntity(immovable);

		m_window.clear();
		render();
		m_viewport.setCenter(player.getPosition());
		m_window.setView(m_viewport);
		m_window.display();
	}
}

void Engine::update() {
	m_deltaTime = m_deltaClock.restart();
	//Console::Info(std::to_string(1 / deltaTime()));
	physicsUpdate();

}

void Engine::physicsUpdate() {
	Collider::GlobalCollision();
}

void Engine::render() {

	for (int i = 0; i < Layer::FINAL; ++i) {
		if (i == Layer::ENTITY) {
			//sf::Vector2f pos = m_collidableStack.at(0)->getPosition();
			//std::sort(m_collidableStack.begin(), m_collidableStack.end(), Collider::zIndex);
			for (int j = 0; j < m_entityStack.size(); ++j) m_window.draw(*m_entityStack.at(j));
			continue;
		}
		m_drawStack[i]->display();
		m_window.draw(sf::Sprite(m_drawStack[i]->getTexture()));
		//_drawStack[Layer::FINAL].draw(sf::Sprite(_drawStack[i].getTexture()));
	}
	//_drawStack[Layer::FINAL].display();
	m_window.draw(sf::Sprite(m_drawStack[Layer::FINAL]->getTexture()));
	refresh();
}

void Engine::refresh() {
	for (int i = 0; i <= Layer::FINAL; ++i) {
		m_drawStack.at(i)->clear(sf::Color::Transparent);
	}
	m_entityStack.clear();
}

void Engine::cleanup() {
	Resource::FlushAll();
	Instance.release();
}