#pragma once

struct CommandLineArgument
{
	public:
		CommandLineArgument(const char* fullName, char shortName, const char* description, bool requiresFollowingArgument);
		const char* FULL_NAME;
		const char SHORT_NAME;
		const char* DESCRIPTION;
		const bool REQUIRES_FOLLOWING_ARGUMENT;
};
