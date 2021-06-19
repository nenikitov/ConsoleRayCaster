#pragma once

#include <functional>

struct AbstractCommandLineArgument
{
	public:
		const char* const FULL_NAME;
		const char SHORT_NAME;
		const char* const DESCRIPTION;
	protected:
		AbstractCommandLineArgument(const char* const fullName, char shortName, const char* const description);
};

