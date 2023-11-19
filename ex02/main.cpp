#include "PmergeMe.hpp"

int isNumber(char *str) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
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
	if (argc % 2 == 0) {
		max = v[max_pos];
		v[max_pos] = v[v.size() - 1];
		v.pop_back();
	}

	PMergeMe p(v.begin(), v.end());
	p.sort(1);

	for (int i = 0; i < v.size(); i++){
		std::cout << v[i] << '\n';
	}
	if (argc % 2 == 0)
		std::cout << max << '\n';
	return 0;
}
