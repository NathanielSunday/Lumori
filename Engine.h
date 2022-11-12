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

class Engine {
public:
	//Execute the programe
	void run();
	//Get the current state of the game
	State state();
	//Get the elapsed time between loops
	float deltaTime();
private:
	//the state the game is currently in
	State _state;
	//the main window fo the game
	sf::RenderWindow _window;
	//the main viewport of the game
	sf::View _viewport;
	//The clock used for calculating time between loops
	sf::Clock _deltaTime;

	//Pre-window variables set
	void initEngine();
	//Window variables set
	void initWindow();
	//The main viewport (should probably be called when the player is loaded)
	void initViewport();
	//The main loop of the game
	void mainLoop();
	//cleanup the residuals before closing the game
	void cleanup();
};

//the main gameplay loop
int main();
