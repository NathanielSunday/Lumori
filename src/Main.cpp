#include <Lumori/Engine/Engine.hpp>
#include <Lumori/Engine/Console.hpp>

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