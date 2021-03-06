#include "ArgumentParser.h"

ArgumentParser::ArgumentParser()
{
	simpleArguments = std::vector<SimpleCommandLineArgument>();
	complexArguments = std::vector<ComplexCommandLineArgument>();
}

void ArgumentParser::addArgumentToParser(AbstractCommandLineArgument& argument)
{
	if (argument.getIsComplex())
		complexArguments.push_back((ComplexCommandLineArgument&)argument);
	else
		simpleArguments.push_back((SimpleCommandLineArgument&)argument);
}

void ArgumentParser::parse(int argc, char* argv[])
{
	ArgumentParser self = ArgumentParser(*this);

	for (int i = 0; i < simpleArguments.size(); i++)
	{
		if (ArgumentReader::containsSimple(argc, argv, simpleArguments[i]))
			simpleArguments[i].ACTION();
	}

	for (int i = 0; i < complexArguments.size(); i++)
	{
		std::string out = "";
		if (ArgumentReader::containsComplex(argc, argv, complexArguments[i], out))
			complexArguments[i].ACTION(out);
		else
		{
			if (complexArguments[i].REQUIRED)
			{
				std::string name = complexArguments[i].FULL_NAME;
				throw std::invalid_argument("Required argument '" + name + "' was not received");
			}
		}
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
	for (int i = 0; i < this->complexArguments.size(); i++)
	{
		std::cout << "-" << complexArguments[i].SHORT_NAME << std::endl;
		std::cout << "--" << complexArguments[i].FULL_NAME << std::endl;
		if (complexArguments[i].REQUIRED)
			std::cout << "REQUIRED" << std::endl;
		std::cout << "\t" << complexArguments[i].DESCRIPTION << std::endl;
		std::cout << std::endl;
	}
}
