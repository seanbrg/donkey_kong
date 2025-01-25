#pragma once

#include <iostream>
#include <list>

/*
* handles the creation or loading of a .steps file which records all moves made in a single game.
*/
class Steps {
	size_t* point_of_time;
	bool colors;
	int difficulty;
	long randomSeed = 0; // used for making the rand() inside donkey kong games deterministic
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step

public:

	/*
	* constructor for Steps object
	* @param _pot: pointer to a point_of_time iterator from a game being saved.
	* @param _diff: difficulty of the game being saved.
	*/
	Steps(size_t* _pot = 0, int _diff = 2) : point_of_time(_pot), difficulty(_diff) {}

	/*
	* load this object's contents from a file.
	* @param filename: name of file to load from. should end with '.steps'.
	*/
	void loadSteps(const std::string& filename);

	/*
	* save this object's contents into a file.
	* @param filename: name of file to save into. should end with '.steps'.
	*/
	void saveSteps(const std::string& filename) const;
	
	/*
	* get the randomizer seed saved in this Steps object.
	* @return the random seed saved.
	*/
	long getRandomSeed() const { return randomSeed; }
	
	/*
	* set this object's saved randomizer seed.
	* @param seed: randomizer seed from a donkey kong game.
	*/
	void setRandomSeed(long seed) { randomSeed = seed; }
	

	/*
	* get the difficulty level saved in this Steps object.
	* @return the difficulty level saved.
	*/
	int getDifficulty() const { return difficulty; }

	/*
	* set this object's saved difficulty level.
	* @param diff: difficulty of a donkey kong game.
	*/
	void setDifficulty(int diff) { difficulty = diff; }

	/*
	* get the colors setting saved in this Steps object.
	* @return the colors setting.
	*/
	bool getColors() const { return colors; }

	/*
	* set this Steps object's colors setting.
	* @param col: a colors setting to save.
	*/
	void setColors(bool col) { colors = col; }

	/*
	* save to the steps list a new step made by the player during the game.
	* @param iteration: number of iteration (point-of-time) in which the step was made.
	* @param step: character (or Key) representing the player's move as is handled by the game.
	*/
	void addStep(size_t iteration, char step) { steps.push_back({ iteration, step }); }
	
	/*
	* returns whether a specific iteration is the time in which the next step in the list is made.
	* @param iteration: a specific iteration (point-of-time).
	* @return whether it's the next step.
	*/
	bool isNextStep(size_t iteration) const { return !steps.empty() && steps.front().first == iteration; }
	
	/*
	* returns whether the steps list is now empty.
	* @return true if empty, false otherwise.
	*/
	bool isEmpty() const { return steps.empty(); }

	/*
	* pop from the steps list the next item.
	* @return the char saved in the popped step, representing a move by the player.
	*/
	char popStep();
};
