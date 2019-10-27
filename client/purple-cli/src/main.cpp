#include <vector>
#include "purple.hpp"

void printUsage()
{
    std::cout   << "purplewallet:" << std::endl
                << "purchase - Add" << std::endl;
}

int	main(int argc, char *argv[])
{
	Purple program;
    std::vector<std::string> vargs(argv, argv + argc);
    vargs.erase(vargs.begin());
	if (argc <= 1)
    {
	    std::cerr << "Error: You must give at least one argument" << std::endl;
	    printUsage();
	    return 1;
    }
	return program.run(vargs);
}
