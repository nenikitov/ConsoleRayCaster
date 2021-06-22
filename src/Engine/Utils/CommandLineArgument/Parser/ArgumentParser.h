#pragma once

#include "../Reader/ArgumentReader.h"
#include <vector>
#include <string>
#include <iostream>

class ArgumentParser
{
	public:
		ArgumentParser();
		void addArgumentToParser(AbstractCommandLineArgument& argument);
		void parse(int argc, char* argv[]);
		void printHelp(const char* appName, const char* appDescription);
	private:
		std::vector<SimpleCommandLineArgument> simpleArguments;
		std::vector<ComplexCommandLineArgument> complexArguments;

		const char* SEPARATOR = "----------\n";
};
