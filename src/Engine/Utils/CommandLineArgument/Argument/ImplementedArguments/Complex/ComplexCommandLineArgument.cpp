#include "ComplexCommandLineArgument.h"

ComplexCommandLineArgument::ComplexCommandLineArgument(const char* const fullName, char shortName, const char* const description, std::function<void(std::string& out)> action)
	: AbstractCommandLineArgument(fullName, shortName, description), ACTION(action)
{}

const bool ComplexCommandLineArgument::getIsComplex()
{
	return true;
}
