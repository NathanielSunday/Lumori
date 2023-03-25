#include "Console.hpp"
#include <iostream>

void Console::WriteLine(std::string message, ConsoleType type, bool newLine, bool isFormat) {	
	//Cool useful embedded macros
	//__FILE__
	//__DATE__
	//__TIME__
	//__LINE__
	if (!isFormat) {
		out(message, newLine);
		return;
	}


	switch(type) {
		case DEBUG:
#ifndef NDEBUG
			message = "\033[1;32mDEBUG\033[0m " + message;
#endif //making sure not explicitly not debug
			break;
		case INFO:
			message = "\033[1;36mINFO\033[0m " + message;
			break;
		case WARN:
			message = "\033[1;33mWARN\033[0m " + message;
			break;
		default:
			message = "INVALID MESSAGE TYPE!";
		case ERROR:
			message = "\033[1;31mERROR\033[0m " + message;
			break;
	}

	format(message);
	out(message, newLine);

}

void Console::Debug(std::string message) {
	WriteLine(message, ConsoleType::DEBUG);
}

void Console::Info(std::string message) {
	WriteLine(message, ConsoleType::INFO);
}

void Console::Warn(std::string message) {
	WriteLine(message, ConsoleType::WARN);
}

void Console::Error(std::string message) {
	WriteLine(message, ConsoleType::ERROR);
}

void Console::format(std::string &message) {
	time_t now = time(0);
	tm ltm{};
#if defined(_MSC_VER)
	localtime_s(&ltm, &now);
#elif defined(__unix__)
	localtime_r(&now, &ltm);
#else
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);
	ltm = *std::localtime(&ltm);
#endif
	std::string fmt = "%F %T";
	char buf[64];
	std::string timestamp = {buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &ltm)};

	message = "\033[35m[" + timestamp + "]\033[0m " + message;
}

void Console::out(std::string &message, bool newLine) {
	std::cout << message << (newLine ? "\n" : "");
}
