#pragma once

#include "../../AbstractArgument/AbstractCommandLineArgument.h"

struct SimpleCommandLineArgument : public AbstractCommandLineArgument
{
	public:
		SimpleCommandLineArgument(const char* const fullName, char shortName, const char* const description, std::function<void()> action);
		const std::function<void()> ACTION;
		const bool getIsComplex() override;
};
