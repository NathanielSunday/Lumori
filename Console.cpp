#include "Console.h"

void Console::WriteLine(std::string message, ConsoleType type, bool newLine) {
	std::string format;
	std::string color;
	
	//Cool useful embedded macros
	//__FILE__
	//__DATE__
	//__TIME__
	//__LINE__

	switch(type) {
		case DEBUG:
			color ="\033[1;32m";
			format = "DEBUG";
			break;
		case INFO:
			color = "\033[1;36m";
			format = "INFO";
			break;
		case WARN:
			color = "\033[1;33m";
			format = "WARN";
			break;
		case ERROR:
			color = "\033[1;31m";
			format = "ERROR";
			break;
	}

	std::cout << "\033[35m[" __DATE__ " | " __TIME__ "] " << color << format << "\033[0m " << message << (newLine ? "\n" : "");
}
