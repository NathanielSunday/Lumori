#pragma once
#include <Lumori/Interaction/Entity.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>


enum State {
	/*
	//Opening credits????
	INTRO,
	//The main menu/start screen
	MAIN_MENU,
	//Select a saved game state
	SAVE_SELECT,
	//Initial multiplayer lobby, meant for setting up a game
	MULTIPLAYER_LOBBY,
	*/
	//the main play scene, where the game takes place
	PLAY,
	//The pause scene, anything equal to greater than this should pause animations client side.
	PAUSE,
	//inventory screen (not sure if this is required, but I figure it's safer to have)
	INVENTORY,
	//Map screen (see above)
	MAP,
};

enum Layer {
	//baked
	BACKGROUND,	
	//not baked
	ENTITY,		
	//baked
	FOREGROUND,	
	//baked
	INTERFACE,	
	//Last layer, for ease of access
	FINAL		
};

class Engine {
public:
	static std::unique_ptr<Engine> Instance;


	/// Executes the program
	void run();

	/// <returns>the current state of the game</returns>
	State state();

	/// <returns>elapsed time as seconds</returns>
	float deltaTime();

	// Draws to a specific render layer
	void drawToLayer(const sf::Drawable& drawable, Layer layer, const sf::RenderStates& states = sf::RenderStates::Default);

	//and entity to entity draw stack
	void addEntity(Entity& entity);

private:
	//The current state that the game is in
	State m_state;

	//The main window of the game
	sf::RenderWindow m_window;

	//The main player's viewport
	sf::View m_viewport;

	//The clock used for logical calculation (i.e. deltaTime)
	sf::Clock m_deltaClock;
	
	//The time used in the deltaTime() function
	sf::Time m_deltaTime;

	//The draw stack
	std::vector<sf::RenderTexture*> m_drawStack;

	//A stack of moving entities to be drawn as a kind of drawstack
	std::vector<Entity*> m_entityStack;


	//Pre-window variables and parameter setting
	void initEngine();

	//Initialize the window and subsidaries
	void initWindow();

	//Initialize the main viewport (use when loading the player or changing video settings)
	void initViewport();

	//The main game loop
	void mainLoop();

	//Logical update
	void update();

	//Checks collider list, then moves accordingly
	void physicsUpdate();

	//Finalizes the render texture from the draw stack before drawing it on the screen
	void render();

	//Refresh the draw stack
	void refresh();

	//Clean up residuals before program termination
	void cleanup();
};

