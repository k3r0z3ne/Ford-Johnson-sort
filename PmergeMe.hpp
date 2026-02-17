#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

class PmergeMe {
	private:
		std::vector<int>	vectorType_;
		std::deque<int>		dequeType_;

		PmergeMe();
		template <typename Container> Container	sortContainer( Container &inputList );
		template <typename Container> Container	insertSort( Container &low, Container &high, Container &pending );

		template <typename Container> typename Container::iterator	binarySearch( Container &container, int value );

		std::vector<int>	generateJacobsthal( size_t maxSize );
		std::vector<int>	createInsertionSequence( size_t pendingSize );
		double				getCurrentTime( void ) const;
	public:
		~PmergeMe();
		PmergeMe( const std::list<int> &inputList );
		PmergeMe( const PmergeMe &other );
		PmergeMe &operator=( const PmergeMe &other );

		template <typename Container> static bool	isSorted( const Container &list );
		static std::list<int>	parseInput( const int argc, const char **argv );
};

template <typename Container> bool	PmergeMe::isSorted( const Container &list ) {
	if (list.size() <= 1)
		return (true);
	typename Container::const_iterator it = list.begin();
	int	prev = *it;
	++it;
	while (it != list.end()) {
		if (*it < prev)
			return (false);
		prev = *it;
		++it;
	}
	return (true);
}

# endif