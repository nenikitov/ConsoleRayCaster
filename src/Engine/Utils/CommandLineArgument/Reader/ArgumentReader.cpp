#include "ArgumentReader.h"

bool ArgumentReader::containsSimple(int argc, char* argv[], CommandLineArgument& argument)
{

}

bool ArgumentReader::containsWithFollowingArgument(int argc, char* argv[], CommandLineArgument& argument, std::string& outArgument)
{
    const bool CONTAINS = ArgumentReader::containsSimple(argc, argv, argument);

    if (!CONTAINS)
        return false;

    if (!argument.REQUIRES_FOLLOWING_ARGUMENT)
    {
        outArgument = "";
        return true;
    }

    for (int i = 1; i < argc; i++)
    {
        const std::string CURRENT_ARG = argv[i];

        if (CURRENT_ARG.substr(0, 2) == "--")
        {
            // Full name
            if (CURRENT_ARG.find(argument.FULL_NAME) != -1)
                return true;
        }
        else if (CURRENT_ARG.substr(0, 1) == "-")
        {
            // Short name
            if (CURRENT_ARG.find(argument.SHORT_NAME) != -1)
                return true;
        }

        return false;
    }

    return false;
}

bool ArgumentReader::findArgument(int argc, char* argv[], CommandLineArgument& argument, int& index)
{

    return false;
}
