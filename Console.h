#pragma once
#include <string>
#include <iostream>


enum ConsoleType {
	DEBUG,		//green
	INFO,		//white
	WARN,		//yellow
	ERROR,		//red
};

class Console {
public:
	//Write a line to the console using proper formatting.
	static void WriteLine(std::string message, ConsoleType type = ConsoleType::INFO, bool newLine = true);
};

