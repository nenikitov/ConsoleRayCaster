#pragma once

#include "../Reader/ArgumentReader.h"
#include <functional>
#include <vector>
#include <string>
#include <iostream>

class ArgumentParser
{
	public:
		ArgumentParser();
		void addSimpleArgumentToParser(const char* fullName, char shortName, const char* description, std::function<void()> function);
		void addArgumentWithOptionsToParser(const char* fullName, char shortName, const char* description, std::function<void(std::string&)> function);
		void parse(int argc, char* argv[]);
		void printHelp(const char* appName, const char* appDescription);
	private:
		std::vector<CommandLineArgument> simpleArguments;
		std::vector<std::function<void()>> simpleArgumentsFunctions;
		std::vector<CommandLineArgument> argumentsWithOptions;
		std::vector<std::function<void(std::string&)>> argumentsWithOptionsMethods;

		const char* SEPARATOR = "----------\n";
};
