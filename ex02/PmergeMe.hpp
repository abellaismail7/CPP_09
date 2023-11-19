#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <list>

#define nodelist std::vector<node>

#define Vec std::vector<int>
#define RandomAccessIterator Vec::iterator 
#define numlist std::list<RandomAccessIterator>


struct node {
	RandomAccessIterator value;
	numlist::iterator main;
	size_t index;
};

class PMergeMe {
	RandomAccessIterator start;
	RandomAccessIterator end;
public:
	PMergeMe(RandomAccessIterator start, RandomAccessIterator end);
	~PMergeMe();
	void sort(size_t steps);
};


int count_by_steps(RandomAccessIterator start, RandomAccessIterator end, size_t steps);
void swap_ranges(RandomAccessIterator start, int steps);
void insert(numlist &main_chain, nodelist::iterator bound, nodelist &pending_chain, size_t steps);
size_t jacob(int i);
