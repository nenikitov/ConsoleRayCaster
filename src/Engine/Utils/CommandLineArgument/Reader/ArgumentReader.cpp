#include "ArgumentReader.h"

bool ArgumentReader::containsSimple(int argc, char* argv[], CommandLineArgument& argument)
{
    int index;
    return ArgumentReader::findArgument(argc, argv, argument, index);
}

bool ArgumentReader::containsWithFollowingArgument(int argc, char* argv[], CommandLineArgument& argument, std::string& outArgument)
{
    int index;
    const bool CONTAINS = ArgumentReader::findArgument(argc, argv, argument, index);
    const bool HAS_NEXT_OPTION = ArgumentReader::isFollowingOption(index + 1, argc, argv);

    if (!CONTAINS)
        return false;

    if (HAS_NEXT_OPTION)
    {
        outArgument = argv[index + 1];
        return true;
    }
    else
    {
        std::string currentArg = argv[index];
        currentArg.erase(0, currentArg.find("=") + 1);

        outArgument = currentArg;
        return true;
    }

    return false;
}

bool ArgumentReader::findArgument(int argc, char* argv[], CommandLineArgument& argument, int& index)
{
    for (int i = 1; i < argc; i++)
    {
        const std::string CURRENT_ARG = argv[i];
        const bool HAS_NEXT_OPTION = ArgumentReader::isFollowingOption(i + 1, argc, argv);
        const bool CONTAINS_EQUALS = (CURRENT_ARG.find("=") != -1);

        if (ArgumentReader::isFullNameArgument(i, argc, argv))
        {
            const std::string PREFIX = std::string("--") + argument.FULL_NAME;

            if (argument.REQUIRES_FOLLOWING_ARGUMENT)
            {
                if (CURRENT_ARG.rfind(PREFIX, 0) == 0)
                {
                    if (CONTAINS_EQUALS || HAS_NEXT_OPTION)
                    {
                        index = i;
                        return true;
                    }
                }
            }
            else
            {
                if (CURRENT_ARG == PREFIX && !HAS_NEXT_OPTION)
                {
                    index = i;
                    return true;
                }
            }
        }
        else if (ArgumentReader::isShortNameArgument(i, argc, argv))
        {
            const std::string PREFIX = std::string("-") + argument.SHORT_NAME;

            if (argument.REQUIRES_FOLLOWING_ARGUMENT)
            {
                if (CURRENT_ARG.rfind(PREFIX, 0) == 0)
                {
                    if (CONTAINS_EQUALS || HAS_NEXT_OPTION)
                    {
                        index = i;
                        return true;
                    }
                }
            }
            else
            {
                if ((CURRENT_ARG.find(argument.SHORT_NAME) != -1) && !CONTAINS_EQUALS && !HAS_NEXT_OPTION)
                {
                    index = i;
                    return true;
                }
            }
        }
    }

    index = -1;
    return false;
}

bool ArgumentReader::isShortNameArgument(int index, int argc, char* argv[])
{
    if (index < 0 || index >= argc)
        return false;

    const std::string CURRENT_ARG = argv[index];

    if (ArgumentReader::isFullNameArgument(index, argc, argv))
        return false;

    return (CURRENT_ARG.rfind("-", 0) == 0);
}

bool ArgumentReader::isFullNameArgument(int index, int argc, char* argv[])
{
    if (index < 0 || index >= argc)
        return false;

    const std::string CURRENT_ARG = argv[index];

    return (CURRENT_ARG.rfind("--", 0) == 0);
}

bool ArgumentReader::isFollowingOption(int index, int argc, char* argv[])
{
    if (index < 0 || index >= argc)
        return false;

    const std::string CURRENT_ARG = argv[index];

    return (CURRENT_ARG.rfind("-", 0) != 0);
}
