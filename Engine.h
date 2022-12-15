#pragma once

#include "Resource.h"
#include "Level.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <memory>



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
	BACKGROUND,
	MIDGROUND,
	FOREGROUND,
	INTERFACE,
	//DO NOT DRAW TO THIS LAYER
	FINAL,
};

class Engine {
public:

	/// <summary>
	/// Executes the program
	/// </summary>
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
	void drawToLayer(Layer layer, const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

private:
	/// <summary>
	/// The current state that the game is in
	/// </summary>
	State _state;

	/// <summary>
	/// The main window of the game
	/// </summary>
	sf::RenderWindow _window;

	/// <summary>
	/// The main player's viewport
	/// </summary>
	sf::View _viewport;
	
	/// <summary>
	///	The clock used for logical calculation (i.e. deltaTime)
	/// </summary>
	sf::Clock _deltaClock;
	
	/// <summary>
	/// The time used in the deltaTime() function
	/// </summary>
	sf::Time _deltaTime;
	
	//perhaps instead make the background and hud a rendertexture in their specific classes, and everything else is an array of drawables and states in which to draw them

	/// <summary>
	/// The draw stack
	/// </summary>
	sf::RenderTexture* _drawStack;

	/// <summary>
	/// Pre-window variables and parameter setting
	/// </summary>
	void initEngine();

	/// <summary>
	/// Initialize the window and subsidaries
	/// </summary>
	void initWindow();

	/// <summary>
	/// Initialize the main viewport (use when loading the player or changing video settings)
	/// </summary>
	void initViewport();

	/// <summary>
	/// The main game loop
	/// </summary>
	void mainLoop();

	/// <summary>
	/// Finalizes the render texture from the draw stack before drawing it on the screen
	/// </summary>
	void render();

	/// <summary>
	/// Refresh the draw stack
	/// </summary>
	void refresh();

	/// <summary>
	/// Clean up residuals before program termination
	/// </summary>
	void cleanup();
};

//the initial push :)
int main();
