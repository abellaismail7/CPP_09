#include "PmergeMe.hpp"
#include <chrono>

#include <ctime>


int isNumber(char *str) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
}

void printVec(Vec &v, int max) {
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	if (max >= 0)
		std::cout << max;
	std::cout << '\n';
}

int main (int argc, char *argv[]) {
	int i = 1;
	size_t max_pos = 0;
	int max = 0;
	Vec v;
	v.reserve(argc);

	for (size_t i = 1; i < argc; i++) {
		if (!isNumber(argv[i])) {
			std::cout << "Invalid input " <<  argv[i] << "\n";
			return 0;
		}
		int a = atoi(argv[i]);
		if (v[max_pos] < a)
			max_pos = i - 1;
		v.push_back(a);
	}
	std::cout << "Before: ";
	printVec(v, -1);

  clock_t start_time = clock();
	if (argc % 2 == 0) {
		max = v[max_pos];
		v[max_pos] = v[v.size() - 1];
		v.pop_back();
	}
	else
		max = -1;

	PMergeMe p(v.begin(), v.end());
	p.sort(1);
  clock_t end_time = clock();

	std::cout << "After: ";
	printVec(v, max);
	std::cout << "Time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "\n";
	return 0;
}
