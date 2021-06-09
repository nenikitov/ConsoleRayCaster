#include "CommandLineArgument.h"

CommandLineArgument::CommandLineArgument(char* fullName, char shortName, bool isOption)
	: FULL_NAME(fullName), SHORT_NAME(shortName), IS_OPTION(isOption) { }
