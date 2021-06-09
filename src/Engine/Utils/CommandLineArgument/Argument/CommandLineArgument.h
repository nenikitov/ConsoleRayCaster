#pragma once

struct CommandLineArgument
{
	public:
		CommandLineArgument(char* fullName, char shortName, bool isOption);
		const char* FULL_NAME;
		const char SHORT_NAME;
		const bool IS_OPTION;
};
