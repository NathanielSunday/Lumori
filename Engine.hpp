#pragma once

#include <SFML/Graphics.hpp>
#include "Collidable.hpp"




enum State {
	//Opening credits????
	INTRO,
	//The main menu/start screen
	MAIN_MENU,
	//Select a saved game state
	SAVE_SELECT,
	//Initial multiplayer lobby, meant for setting up a game
	MULTIPLAYER_LOBBY,
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

	/// Executes the program
	void run();

	/// <summary>
	///
	/// </summary>
	/// <returns>Returns the current state of the game.</returns>
	State state();

	/// <summary>
	/// Get the elapsed time between game loops
	/// </summary>
	/// <returns>elapsed time as seconds</returns>
	float deltaTime();

	/// <summary>
	/// Draws to a specific render layer
	/// </summary>
	/// <param name="layer">The layer in which to draw</param>
	/// <param name="drawable">The object to draw</param>
	/// <param name="states">The state in which to draw the object</param>
	void drawToLayer(const sf::Drawable& drawable, Layer layer, const sf::RenderStates& states = sf::RenderStates::Default);
	void addCollidable(Collidable& collidable);

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
	sf::RenderTexture* m_drawStack;

	//A stack of moving entities to be drawn as a kind of drawstack
	std::vector<Collidable*> m_collidableStack;

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

	//Finalizes the render texture from the draw stack before drawing it on the screen
	void render();

	//Refresh the draw stack
	void refresh();

	//Clean up residuals before program termination
	void cleanup();
};

//the initial push :)
int main();
