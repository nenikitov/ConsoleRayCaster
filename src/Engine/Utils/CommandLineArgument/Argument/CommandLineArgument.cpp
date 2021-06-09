#include "CommandLineArgument.h"

CommandLineArgument::CommandLineArgument(char* fullName, char shortName, bool isOption)
	: FULL_NAME(fullName), SHORT_NAME(shortName), REQUIRES_FOLLOWING_ARGUMENT(isOption) { }
