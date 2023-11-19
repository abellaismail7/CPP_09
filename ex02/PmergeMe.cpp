#include "PmergeMe.hpp"

PMergeMe::PMergeMe(RandomAccessIterator start, RandomAccessIterator end) {
	this->start = start;
	this->end = end;
}

PMergeMe::~PMergeMe() { 
	// useless destructor just as the corrector
}

void PMergeMe::sort(size_t steps) {
	int count = count_by_steps(start, end, steps);
	if (count <= 1) {
		return;
	}
	for (int i = 0; i + steps < count * steps; i+= steps * 2) {
		swap_ranges(start + i, steps);
	}
	
	sort(steps * 2);
	numlist main_chain;
	nodelist pending_chain;


	main_chain.push_back(start);
	main_chain.push_back(start + steps);
	for (int i = 2; i < count; i+= 2) {
		size_t ri = i * steps;

		main_chain.push_back(start + ri + steps);
		numlist::iterator last = main_chain.end();
		last--;

		Node node = {
			start + ri,
			last,
			steps
		};

		pending_chain.push_back(node);
	}

	int i = 1; // 0 already sorted
	while (true) {
		size_t dist = jacob(i);
		if (dist >= pending_chain.size()) {
			break;
		}
		nodelist::iterator bound = pending_chain.begin() + dist;
		while (true) {
			insert(main_chain, bound, pending_chain, steps);
			pending_chain.erase(bound);
			if (bound == pending_chain.begin())
				break;
			bound--;
		}
		i++;
	}

	while (pending_chain.size() > 0) {
		nodelist::iterator it = pending_chain.begin();
		insert(main_chain, it, pending_chain, steps);
		pending_chain.erase(it);
	}

	std::vector<int> temp;
	temp.reserve(count * steps);
	for (numlist::iterator it = main_chain.begin(); it != main_chain.end(); it++) {
		for (int i = 0; i < steps; i++)
			temp.push_back((*it)[i]);
	}

	std::copy(temp.begin(), temp.end(), start);
}

size_t jacob(int i) {
	if (i == 1)
		return 2;
	if (i == 2)
		return 2;
	return jacob(i - 1) + 2 * jacob(i - 2) ;
}

int count_by_steps(RandomAccessIterator start, RandomAccessIterator end, size_t steps) {
	int count = std::distance(start,end);
	return count / steps;
}

void swap_ranges(RandomAccessIterator start, int steps) {
	RandomAccessIterator next = start + steps;
	if (start[steps -1] < next[steps - 1])
		return;
	for (int i = 0; i < steps; i++) {
		std::swap(start[i], next[i]);
	}
}

bool compare(const std::vector<Node>::iterator b, const RandomAccessIterator a) {
	return a[b->steps - 1] > b->value[b->steps -1];
}

bool PMergeMe::compareInt(int a, int b) {
	return a < b;
}

void insert(numlist &main_chain, nodelist::iterator bound, nodelist &pending_chain, size_t steps) {
			numlist::iterator pos =  std::upper_bound(main_chain.begin(), bound->main, bound, compare); 
			main_chain.insert(pos, bound->value);
}


