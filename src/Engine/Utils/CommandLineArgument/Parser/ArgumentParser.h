#pragma once

#include "../Argument/CommandLineArgument.h"
#include <functional>
#include <vector>

class ArgumentParser
{
	public:
		ArgumentParser();
		void addSimpleArgumentToParser();
		void addArgumentWithOptionsToParser();
	private:
		std::vector<CommandLineArgument> simpleArguments;
		std::vector<std::function<void()>> simpleArgumentsFunctions;
		std::vector<CommandLineArgument> argumentsWithOptions;
		std::vector<std::function<void(int&)>> argumentsWithOptionsMethods;
};
