#include "ComplexCommandLineArgument.h"

ComplexCommandLineArgument::ComplexCommandLineArgument(const char* const fullName, char shortName, const char* const description, bool required, std::function<void(std::string& out)> action)
	: AbstractCommandLineArgument(fullName, shortName, description), ACTION(action), REQUIRED(required)
{}

const bool ComplexCommandLineArgument::getIsComplex()
{
	return true;
}
