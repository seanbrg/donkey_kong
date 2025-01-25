#include <iostream>
#include <limits>
#include <fstream>
#include "results.h"

bool Results::compare(Results& other)
{
	if (other.results.size() != results.size()) {
		std::cout << "Results file error: incorrect number of results.\n";
		return false;
	}

	bool res = true;
	int size = results.size();

	for (int i = 0; i < size; i++) {
		auto my_result = results.front();
		auto others_result = other.results.front();
		results.pop_front();
		other.results.pop_front();

		if (my_result.first != others_result.first || my_result.second != others_result.second) {
			res = false;
			switch (my_result.second) {
			case died:
				std::cout << "Results file error: wrong record of death at t:" << my_result.first << "\n";
				break;
			case finished:
				std::cout << "Results file error: wrong record of victory at t:" << my_result.first << "\n";
				break;
			case score:
				std::cout << "Results file error: wrong record of score: " << my_result.first << "\n";
				break;
			case noResult:
				std::cout << "Results file error: no results recorded\n";
				break;
			}
		}
	}
	return res;
}

void Results::loadResults(const std::string& filename)
{
	std::ifstream results_file(filename);
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		addResult(iteration, static_cast<ResultValue>(result));
	}
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file.close();
}

std::pair<size_t, Results::ResultValue> Results::popResult()
{
	if (results.empty()) return { 0, Results::noResult };
	auto result = results.front();
	results.pop_front();
	return result;
}
