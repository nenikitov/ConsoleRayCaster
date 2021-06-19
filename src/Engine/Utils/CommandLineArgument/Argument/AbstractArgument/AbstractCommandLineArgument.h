#pragma once

struct AbstractCommandLineArgument
{
	public:
		const char* const FULL_NAME;
		const char SHORT_NAME;
		const char* DESCRIPTION;
	protected:
		AbstractCommandLineArgument(const char* const fullName, char shortName, const char* description);
};

