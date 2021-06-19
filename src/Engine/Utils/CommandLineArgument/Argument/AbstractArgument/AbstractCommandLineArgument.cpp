#include "AbstractCommandLineArgument.h"

AbstractCommandLineArgument::AbstractCommandLineArgument(const char* const fullName, char shortName, const char* description)
	: FULL_NAME(fullName), SHORT_NAME(shortName), DESCRIPTION(description)
{ }