#pragma once

#include "../Argument/ImplementedArguments/Simple/SimpleCommandLineArgument.h"
#include "../Argument/ImplementedArguments/Complex/ComplexCommandLineArgument.h"
#include <string>

class ArgumentReader
{
	public:
		static bool containsSimple(int argc, char* argv[], SimpleCommandLineArgument& argument);
		static bool containsComplex(int argc, char* argv[], ComplexCommandLineArgument& argument, std::string& outArgument);
	private:
		static bool findArgument(int argc, char* argv[], AbstractCommandLineArgument& argument, int& index);
		static bool isShortNameArgument(int index, int argc, char* argv[]);
		static bool isFullNameArgument(int index, int argc, char* argv[]);
		static bool isFollowingOption(int index, int argc, char* argv[]);
};
