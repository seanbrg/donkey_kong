#include <iostream>
#include <limits>
#include <fstream>
#include "results.h"

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

size_t Results::getNextDeathIteration() const
{
	if (!results.empty() && results.front().second == died) {
		return results.front().first;
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}
