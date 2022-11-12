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
	static void WriteLine(std::string message, ConsoleType type = ConsoleType::INFO, bool newLine = true, bool format = true);
	static void Debug(std::string message);
	static void Info(std::string message);
	static void Warn(std::string message);
	static void Error(std::string message);
private:
	static void format(std::string &message);
	static void out(std::string &message, bool newLine);
};

