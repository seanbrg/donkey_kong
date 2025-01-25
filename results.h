#pragma once

#include <iostream>
#include <list>

/*
* handles the creation or loading of a .result file which records a game's results.
*/
class Results {
public:
	enum ResultValue { died, finished, score, noResult };

private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result

public:

	/*
	* compare this object with another Results object and print any differences between them.
	* @param other: another Results object to compare with.
	* @return true if the two objects are identical, false if not.
	*/
	bool compare(Results& other);

	/*
	* load this object's contents from a file.
	* @param filename: name of file to load from. should end with '.result'.
	*/
	void loadResults(const std::string& filename);
	
	/*
	* save this object's contents into a file.
	* @param filename: name of file to save into. should end with '.result'.
	*/
	void saveResults(const std::string& filename) const;
	
	/*
	* add a new result item into the list of results.
	* @param iteration: point of time in which this result happened, or otherwise
	* any kind of number associated with this specific result.
	* @param result: the type of result being recorded.
	*/
	void addResult(size_t iteration, ResultValue result) { results.push_back({ iteration, result }); }
	
	/*
	* pop and return the first result in the results list.
	* @return the first result saved in the results list.
	*/
	std::pair<size_t, ResultValue> popResult();
};
