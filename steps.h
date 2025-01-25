#pragma once

#include <iostream>
#include <list>

class Steps {
	size_t* point_of_time;
	bool colors;
	int difficulty;
	long randomSeed = 0;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step

public:

	Steps(size_t* _pot = 0, int _diff = 2) : point_of_time(_pot), difficulty(_diff) {}


	void loadSteps(const std::string& filename);

	
	void saveSteps(const std::string& filename) const;
	
	
	long getRandomSeed() const { return randomSeed; }
	
	
	void setRandomSeed(long seed) { randomSeed = seed; }
	

	int getDifficulty() const { return difficulty; }


	void setDifficulty(int diff) { difficulty = diff; }

	
	bool getColors() const { return colors; }


	void setColors(bool col) { colors = col; }


	void addStep(size_t iteration, char step) { steps.push_back({ iteration, step }); }
	
	
	bool isNextStep(size_t iteration) const { return !steps.empty() && steps.front().first == iteration; }
	
	
	bool isEmpty() const { return steps.empty(); }


	char popStep();
};
