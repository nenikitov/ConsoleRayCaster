#pragma once

#include "../Argument/CommandLineArgument.h"
#include <string>

class ArgumentReader
{
	public:
		static bool containsSimple(int argc, char* argv[], CommandLineArgument& argument);
		static bool containsWithFollowingArgument(int argc, char* argv[], CommandLineArgument& argument, std::string& outArgument);
	private:
		static bool findArgument(int argc, char* argv[], CommandLineArgument& argument, int& index);
		static bool isShortNameArgument(int index, int argc, char* argv[]);
		static bool isFullNameArgument(int index, int argc, char* argv[]);
		static bool isFollowingOption(int index, int argc, char* argv[]);
};
