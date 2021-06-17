#pragma once

#include "../Reader/ArgumentReader.h"
#include <functional>
#include <vector>
#include <string>

class ArgumentParser
{
	public:
		ArgumentParser();
		void addSimpleArgumentToParser(const char* fullName, char shortName, std::function<void()> function);
		void addArgumentWithOptionsToParser(const char* fullName, char shortName, std::function<void(std::string&)> function);
		void parse(int argc, char* argv[]);
		void printHelp();
	private:
		std::vector<CommandLineArgument> simpleArguments;
		std::vector<std::function<void()>> simpleArgumentsFunctions;
		std::vector<const char*> simpleArgumentDescriptions;
		std::vector<CommandLineArgument> argumentsWithOptions;
		std::vector<std::function<void(std::string&)>> argumentsWithOptionsMethods;
		std::vector<const char*> argumentWithOptionsDescriptions;
};
