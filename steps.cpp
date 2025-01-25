#include <fstream>
#include "steps.h"

void Steps::loadSteps(const std::string& filename) {
	std::ifstream steps_file(filename);
	steps_file >> randomSeed;
	steps_file >> difficulty;
	steps_file >> colors;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		addStep(iteration, step);
	}
	steps_file.close();
}

void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << difficulty << "\n" << colors << "\n" << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}

char Steps::popStep()
{
	char step = steps.front().second;
	steps.pop_front();
	return step;
}
