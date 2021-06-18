#include "CommandLineArgument.h"

CommandLineArgument::CommandLineArgument(const char* fullName, char shortName, const char* description, bool isOption)
	: FULL_NAME(fullName), SHORT_NAME(shortName), DESCRIPTION(description), REQUIRES_FOLLOWING_ARGUMENT(isOption) { }
