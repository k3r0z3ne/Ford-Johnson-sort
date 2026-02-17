#include "PmergeMe.hpp"

int	main( int argc, const char **argv )
{
	if (argc < 2)
		return (std::cout << "Error: bad input.\n", 1);
	else if (argc == 2) {
		std::string check(argv[1]);
		if (check.empty())
			return (std::cout << "Error: empty argument.\n", 1);
	}
	std::list<int>	list = PmergeMe::parseInput(argc, argv);
	if (list.empty()) {
		std::cout << "Error: empty list." << std::endl;
		return (1);
	}
	if (PmergeMe::isSorted(list)) {
		std::cout << "Error: list is already sorted." << std::endl;
		return (1);
	}
	PmergeMe	_sort(list);
	return (0);
}
