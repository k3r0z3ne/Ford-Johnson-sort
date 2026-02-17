#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe( const PmergeMe &other ) {
	*this = other;
}

PmergeMe	&PmergeMe::operator=( const PmergeMe &other ) {
	if (this != &other) {
		vectorType_ = other.vectorType_;
		dequeType_ = other.dequeType_;
	}
	return (*this);
}

PmergeMe::PmergeMe( const std::list<int> &inputList )
	: vectorType_(inputList.begin(), inputList.end()), dequeType_(inputList.begin(), inputList.end()) {
	std::list<int>::const_iterator it = inputList.begin();
	std::list<int>::const_iterator iter = inputList.end();
	std::cout << "Before: ";
	while (it != iter) {
		std::cout << *it << " ";
		*it++;
	}
	std::cout << std::endl;

	double startVector = getCurrentTime();
	vectorType_ = sortContainer(vectorType_);
	double endVector = getCurrentTime();
	double timeVector = endVector - startVector;

	double startDeque = getCurrentTime();
	dequeType_ = sortContainer(dequeType_);
	double endDeque = getCurrentTime();
	double timeDeque = endDeque - startDeque;
	std::cout << "After:  ";
	for (size_t i = 0; i < vectorType_.size(); i++) {
		std::cout << vectorType_[i] << " ";
	}
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vectorType_.size()
			  << " elements with std::vector : " << timeVector << " us" << std::endl;
	std::cout << "Time to process a range of " << dequeType_.size()
			  << " elements with std::deque  : " << timeDeque << " us" << std::endl;
	if (!isSorted(vectorType_) || !isSorted(dequeType_))
		std::cout << "Error: list not sorted." << std::endl;
}

std::list<int>	PmergeMe::parseInput( const int argc, const char **argv ) {
	std::string	str;
	if (argc == 2)
		str = argv[1];
	else {
		for (int i = 1; i < argc; i++) {
			if (i > 1)
				str.append(" ");
			str.append(argv[i]);
		}
	}

	std::list<int>		digitList;
	std::string			token;
	std::istringstream	iss(str);
	while (iss >> token) {
		for (size_t i = 0; i < token.size(); i++) {
			if (!std::isdigit(static_cast<char>(token[i]))) {
				std::cout << "Error: list can contain only numbers.\n";
				return (std::list<int>());
			}
		}
		long	value = std::atol(token.c_str());
		if (value > INT_MAX) {
			std::cout << "Error: list can contain only integers.\n";
			return (std::list<int>());
		}
		digitList.push_back(static_cast<int>(value));
	}
	return (digitList);
}

template <typename Container> Container	PmergeMe::sortContainer( Container &inputList ) {
	if (inputList.size() <= 1)
		return (inputList);
	else if (inputList.size() == 2) {
		Container	ret = inputList;
		if (ret[0] > ret[1])
			std::swap(ret[0], ret[1]);
		return (ret);
	}

	std::vector<std::pair<int, int> > _pairs;
	for (size_t i = 0; i + 1 < inputList.size(); i += 2) {
		int	a = inputList[i];
		int	b = inputList[i + 1];
		if (a <= b)
			_pairs.push_back(std::make_pair(a, b));
		else
			_pairs.push_back(std::make_pair(b, a));
	}

	Container	_pending;
	if (inputList.size() % 2 == 1)
		_pending.push_back(inputList.back());

	Container	low, high;
	for (size_t i = 0; i < _pairs.size(); i++) {
		low.push_back(_pairs[i].first);
		high.push_back(_pairs[i].second);
	}

	for (size_t i = 0; i < high.size() - 1; i++) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < high.size(); j++) {
			if (high[j] < high[minIndex])
				minIndex = j;
		}
		if (minIndex != i) {
			std::swap(high[i], high[minIndex]);
			std::swap(low[i], low[minIndex]);
		}
	}

	Container	ret = insertSort(low, high, _pending);
	return (ret);
}

template <typename Container> Container	PmergeMe::insertSort( Container &low, Container &high, Container &pending ) {
	Container	mainChain = high;
	if (low.empty() && pending.empty())
		return (mainChain);
	if (!low.empty())
		mainChain.insert(mainChain.begin(), low[0]);

	Container	elementsToInsert;
	for (size_t i = 1; i < low.size(); i++)
		elementsToInsert.push_back(low[i]);
	elementsToInsert.insert(elementsToInsert.end(), pending.begin(), pending.end());
	if (elementsToInsert.empty())
		return (mainChain);

	std::vector<int> insertionSequence = createInsertionSequence(elementsToInsert.size());
	for (size_t i = 0; i < insertionSequence.size(); i++) {
		int	index = insertionSequence[i];
		if (index >= 0 && static_cast<size_t>(index) < elementsToInsert.size()) {
			typename Container::iterator pos = binarySearch(mainChain, elementsToInsert[index]);
			mainChain.insert(pos, elementsToInsert[index]);
		}
	}
	return (mainChain);
}

std::vector<int>	PmergeMe::createInsertionSequence( size_t pendingSize ) {
	std::vector<int> insertionSequence;
	if (pendingSize == 0)
		return insertionSequence;
	std::vector<int> jacobsthal = generateJacobsthal(20);
	size_t jacobsthalIndex = 0;
	while (jacobsthalIndex < jacobsthal.size() && 
			static_cast<size_t>(jacobsthal[jacobsthalIndex]) <= pendingSize) {
		jacobsthalIndex++;
	}
	size_t lastJacobsthal = 0;
	for (size_t i = 0; i < jacobsthalIndex; i++) {
		size_t currentJacobsthal = static_cast<size_t>(jacobsthal[i]);
		if (currentJacobsthal > pendingSize)
			currentJacobsthal = pendingSize;

		for (size_t j = currentJacobsthal; j > lastJacobsthal; j--)
			insertionSequence.push_back(static_cast<int>(j - 1));

		lastJacobsthal = currentJacobsthal;
		if (currentJacobsthal >= pendingSize)
			break ;
	}
	for (size_t j = pendingSize; j > lastJacobsthal; j--)
		insertionSequence.push_back(static_cast<int>(j - 1));
	return (insertionSequence);
}

template <typename Container> typename Container::iterator	PmergeMe::binarySearch( Container &container, int value ) {
	typename Container::iterator left = container.begin();
	typename Container::iterator right = container.end();

	while (left != right) {
		typename Container::iterator mid = left;
		typename Container::difference_type distance = std::distance(left, right);
		std::advance(mid, distance / 2);
		if (*mid < value) {
			left = mid;
			++left;
		}
		else
			right = mid;
	}
	return (left);
}

std::vector<int>	PmergeMe::generateJacobsthal( size_t maxSize ) {
	std::vector<int> jacobsthalSeq;
	if (maxSize == 0)
		return jacobsthalSeq;
	if (maxSize >= 1)
		jacobsthalSeq.push_back(1);
	if (maxSize >= 2)
		jacobsthalSeq.push_back(3);

	for (size_t i = 2; i < maxSize; i++) {
		int	next = jacobsthalSeq[i - 1] + 2 * jacobsthalSeq[i - 2];
		jacobsthalSeq.push_back(next);
	}
	return (jacobsthalSeq);
}

double	PmergeMe::getCurrentTime( void ) const {
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}
