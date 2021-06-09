#pragma once

struct CommandLineArgument
{
	public:
		CommandLineArgument(char* fullName, char shortName, bool requiresFollowingArgument);
		const char* FULL_NAME;
		const char SHORT_NAME;
		const bool REQUIRES_FOLLOWING_ARGUMENT;
};
