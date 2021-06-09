#include "CommandLineArgument.h"

CommandLineArgument::CommandLineArgument(const char* fullName, char shortName, bool isOption)
	: FULL_NAME(fullName), SHORT_NAME(shortName), REQUIRES_FOLLOWING_ARGUMENT(isOption) { }
