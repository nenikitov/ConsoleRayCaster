#include "ArgumentParser.h"

ArgumentParser::ArgumentParser()
{
	simpleArguments = std::vector<CommandLineArgument>();
	simpleArgumentsFunctions = std::vector<std::function<void(ArgumentParser& parser)>>();
	argumentsWithOptions = std::vector<CommandLineArgument>();
	argumentsWithOptionsMethods = std::vector<std::function<void(ArgumentParser& parser, std::string&)>>();
}

void ArgumentParser::addSimpleArgumentToParser(const char* fullName, char shortName, const char* description, std::function<void(ArgumentParser& parser)> function)
{
	simpleArguments.push_back(CommandLineArgument(fullName, shortName, description, false));
	simpleArgumentsFunctions.push_back(function);
}

void ArgumentParser::addArgumentWithOptionsToParser(const char* fullName, char shortName, const char* description, std::function<void(ArgumentParser& parser, std::string&)> function)
{
	argumentsWithOptions.push_back(CommandLineArgument(fullName, shortName, description, true));
	argumentsWithOptionsMethods.push_back(function);
}

void ArgumentParser::parse(int argc, char* argv[])
{
	ArgumentParser self = ArgumentParser(*this);

	for (int i = 0; i < simpleArguments.size(); i++)
	{
		if (ArgumentReader::containsSimple(argc, argv, simpleArguments[i]))
			simpleArgumentsFunctions[i](self);
	}

	for (int i = 0; i < argumentsWithOptions.size(); i++)
	{
		std::string out = "";
		if (ArgumentReader::containsWithFollowingArgument(argc, argv, argumentsWithOptions[i], out))
			argumentsWithOptionsMethods[i](self, out);
	}
}

void ArgumentParser::printHelp(const char* appName, const char* appDescription)
{
	std::cout << SEPARATOR;
	std::cout << appName << std::endl;
	
	std::cout << SEPARATOR;
	std::cout << appDescription << std::endl;

	std::cout << SEPARATOR;
	std::cout << "Simple arguments (do not require options after)" << std::endl;
	for (int i = 0; i < this->simpleArguments.size(); i++)
	{
		std::cout << "-" << simpleArguments[i].SHORT_NAME << std::endl;
		std::cout << "--" << simpleArguments[i].FULL_NAME << std::endl;
		std::cout << "\t" << simpleArguments[i].DESCRIPTION << std::endl;
		std::cout << std::endl;
	}

	std::cout << SEPARATOR;
	std::cout << "Complex arguments (require options after)" << std::endl;
	for (int i = 0; i < this->argumentsWithOptions.size(); i++)
	{
		std::cout << "-" << argumentsWithOptions[i].SHORT_NAME << std::endl;
		std::cout << "--" << argumentsWithOptions[i].FULL_NAME << std::endl;
		std::cout << "\t" << argumentsWithOptions[i].DESCRIPTION << std::endl;
		std::cout << std::endl;
	}
}
