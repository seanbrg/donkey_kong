#pragma once

#include <iostream>
#include <list>

class Results {
public:
	enum ResultValue { died, finished, score, noResult };

private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result

public:

	static Results loadResults(const std::string& filename);
	
	
	void saveResults(const std::string& filename) const;
	
	
	void addResult(size_t iteration, ResultValue result) { results.push_back({ iteration, result }); }
	
	
	std::pair<size_t, ResultValue> popResult();
	
	
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || results.back().first <= iteration;
	}
	
	
	size_t getNextDeathIteration() const;
};
