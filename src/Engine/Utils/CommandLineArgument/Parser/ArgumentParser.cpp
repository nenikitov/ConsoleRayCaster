#include "ArgumentParser.h"

ArgumentParser::ArgumentParser()
{
	simpleArguments = std::vector<CommandLineArgument>();
	simpleArgumentsFunctions = std::vector<std::function<void()>>();
	argumentsWithOptions = std::vector<CommandLineArgument>();
	argumentsWithOptionsMethods = std::vector<std::function<void(std::string&)>>();
}

void ArgumentParser::addSimpleArgumentToParser(const char* fullName, char shortName, std::function<void()> function)
{
	simpleArguments.push_back(CommandLineArgument(fullName, shortName, false));
	simpleArgumentsFunctions.push_back(function);
}

void ArgumentParser::addArgumentWithOptionsToParser(const char* fullName, char shortName, std::function<void(std::string&)> function)
{
	argumentsWithOptions.push_back(CommandLineArgument(fullName, shortName, true));
	argumentsWithOptionsMethods.push_back(function);
}

void ArgumentParser::parse(int argc, char* argv[])
{
	for (int i = 0; i < simpleArguments.size(); i++)
	{
		if (ArgumentReader::containsSimple(argc, argv, simpleArguments[i]))
			simpleArgumentsFunctions[i]();
	}

	for (int i = 0; i < argumentsWithOptions.size(); i++)
	{
		std::string out = "";
		if (ArgumentReader::containsWithFollowingArgument(argc, argv, argumentsWithOptions[i], out))
			argumentsWithOptionsMethods[i](out);
	}
}
