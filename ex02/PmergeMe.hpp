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
#include <deque>

#define nodelist std::vector<Node>
#define Vec std::vector<int>
#define RandomAccessIterator Vec::iterator 
#define numlist std::list<RandomAccessIterator>

struct Node {
	RandomAccessIterator value;
	numlist::iterator main;
	size_t steps;
};

#define nodelistdeq std::vector<NodeDeq>
#define Deq std::deque<int>
#define RandomAccessIteratorDeq Deq::iterator 
#define numlistdeq std::list<RandomAccessIteratorDeq>

struct NodeDeq {
	RandomAccessIteratorDeq value;
	numlistdeq::iterator main;
	size_t steps;
};

class PMergeMe {
	RandomAccessIterator start;
	RandomAccessIterator end;

	RandomAccessIteratorDeq start_deq;
	RandomAccessIteratorDeq end_deq;
public:
	static bool compareInt(int a, int b);
	PMergeMe(RandomAccessIterator start, RandomAccessIterator end);
	PMergeMe(RandomAccessIteratorDeq start, RandomAccessIteratorDeq end);
	~PMergeMe();
	void sort(size_t steps);

	void sort_deq(size_t steps);
};


int count_by_steps(RandomAccessIterator start, RandomAccessIterator end, size_t steps);
void swap_ranges(RandomAccessIterator start, int steps);
size_t jacob(int i);

int count_by_steps_deq(RandomAccessIteratorDeq start, RandomAccessIteratorDeq end, size_t steps);
void swap_ranges_deq(RandomAccessIteratorDeq start, int steps);

void insert_deq(numlistdeq &main_chain, nodelistdeq::iterator bound);
void insert(numlist &main_chain, nodelist::iterator bound);

