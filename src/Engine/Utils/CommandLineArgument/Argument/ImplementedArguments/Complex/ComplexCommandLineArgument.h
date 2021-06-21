#pragma once

#include "../../AbstractArgument/AbstractCommandLineArgument.h"
#include <string>

struct ComplexCommandLineArgument : public AbstractCommandLineArgument
{
	public:
		ComplexCommandLineArgument(const char* const fullName, char shortName, const char* const description, bool required, std::function<void(std::string& out)> action);
		const bool REQUIRED;
		const std::function<void(std::string& out)> ACTION;
		const bool getIsComplex() override;
};
