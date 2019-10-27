#include <vector>
#include "purple.hpp"



int	main(int argc, char *argv[])
{
	Purple program;
    std::vector<std::string> vargs(argv, argv + argc);
    vargs.erase(vargs.begin());
	if (argc <= 1)
    {
	    std::cerr << "Error: You must give at least one argument" << std::endl;
	    program.printHelp();
	    return 1;
    }
	return program.run(vargs);
}
