#pragma once

#include "../Argument/CommandLineArgument.h"
#include <string>
#include <regex>

class ArgumentReader
{
	public:
		static bool containsSimple(int argc, char* argv[], CommandLineArgument& argument);
		static bool containsWithFollowingArgument(int argc, char* argv[], CommandLineArgument& argument, std::string& outArgument);
	private:
		static bool findArgument(int argc, char* argv[], CommandLineArgument& argument, int& index);
};
