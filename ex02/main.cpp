#include "PmergeMe.hpp"
#include <chrono>
#include <cstdlib>
#include <deque>
#include <ctime>
#include <vector>

int isNumber(char *str) {
	int i = 0;

	if (strlen(str) > 10)
		return 0;
	if (atol(str) > INT_MAX)
		return 0;
	while (str[i] != '\0') {
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
}

void printVec(Vec &v, int max) {
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	if (max >= 0)
		std::cout << max;
	std::cout << '\n';
}

int parse(std::vector<int> & v, char** values, size_t count) {
	size_t max_pos = 0;
	int max = 0;
	v.reserve(count);

	for (size_t i = 0; i < count; i++) {
		if (!isNumber(values[i])) {
			std::cout << "Error" << "\n";
			return -2;
		}
		int a = atoi(values[i]);
		if (i == 0 || v[max_pos] < a)
			max_pos = i;
		v.push_back(a);
	}
	std::cout << "Before: ";
	printVec(v, -1);

	if (count % 2 == 1) {
		max = v[max_pos];
		v[max_pos] = v[v.size() - 1];
		v.pop_back();
	}
	else
		max = -1;
	return max;
}

double sortVec(std::vector<int> &v) {
	clock_t start_time = clock();
	PMergeMe p(v.begin(), v.end());
	p.sort(1);
	clock_t end_time = clock();

	std::deque<int> d(v.begin(), v.end());
	return (end_time - start_time) / (CLOCKS_PER_SEC / (double) 1000000);
}

double sortDeq(std::deque<int> &d) {
	clock_t start_time = clock();
	PMergeMe p(d.begin(), d.end());
	p.sort_deq(1);
	clock_t end_time = clock();
	return (end_time - start_time) / (CLOCKS_PER_SEC/ (double) 1000000);
}

int main (int argc, char *argv[]) {
	Vec v;
	if (argc < 2) {
		std::cout << "No arguments\n";
		return 0;
	}

	int max = parse(v, argv + 1, argc - 1);
	if (max == -2)
		return 1;
	
	std::deque<int> d(v.begin(), v.end());
	double time_vec = sortVec(v);
	double time_deq = sortDeq(d);

	std::cout << "After:  ";
	printVec(v, max);
	std::cout << "Time to process a range of " << v.size() <<" elements with std::vector : " << std::fixed << time_vec << " µs \n";
	std::cout << "Time to process a range of " << v.size() <<" elements with std::deque  : " << std::fixed << time_deq << " µs \n";
	return 0;
}
