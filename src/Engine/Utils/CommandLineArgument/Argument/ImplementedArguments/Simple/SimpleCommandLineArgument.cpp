#include "SimpleCommandLineArgument.h"

SimpleCommandLineArgument::SimpleCommandLineArgument(const char* const fullName, char shortName, const char* const description, std::function<void()> action)
	: AbstractCommandLineArgument(fullName, shortName, description), ACTION(action)
{}
