#pragma once

#define SUCCESSFUL_EXIT		0x00000000;
#define FAILED_EXIT			0x00000001;




enum State
{
	//The main menu/start screen
	MAIN_MENU,
	//Select a saved game state
	SAVE_SELECT,
	//Initial multiplayer lobby, meant for setting up a game
	MULTIPLAYER_LOBBY,
	//the main play scene, where the game takes place
	PLAY_SCENE,
	//inventory screen (not sure if this is required, but I figure it's safer)
	INVENTORY,

};

//the main gameplay loop
int main();
