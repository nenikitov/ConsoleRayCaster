#pragma once

#include "../Argument/CommandLineArgument.h"
#include <functional>

class ArgumentParser
{
	public:
		ArgumentParser();
		void addSimpleArgumentToParser();
		void addArgumentWithOptionsToParser();
	private:
		CommandLineArgument* simpleArguments;
		std::function<void()>* simpleArgumentsFunctions;
		CommandLineArgument* argumentsWithOptions;
		std::function<void(int&)>* argumentsWithOptionsMethods;
};
