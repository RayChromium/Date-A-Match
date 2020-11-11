#include "Match.h"
#include <iterator>

std::vector<std::pair<std::pair<Person, Person>, float>> 
Male2FemaleDisireDistances(std::vector<Person> persons)
{
	// divide persons into a male and female vector:
	std::vector<Person> males;
	std::vector<Person> females;
	std::cout << "Diciding src data by gender\n";
	std::copy_if(persons.begin(), persons.end(), std::back_inserter(males),
		[](const Person& p)
		{
			return p.IsMale();
		});
	std::copy_if(persons.begin(), persons.end(), std::back_inserter(females),
		[](const Person& p)
		{
			return !p.IsMale();
		});

	std::cout << "Calculating desire distance\n";
	// calculate the "desire distance" and push into the result container
	std::vector<std::pair<std::pair<Person, Person>, float>> result;
	for (size_t i = 0; i < males.size(); ++i)
	{
		for (size_t j = 0; j < females.size(); ++j)
		{
			float dd = males[i].DesireDistance(females[j]);
			result.push_back({ {males[i],females[j]},dd });
		}
	}

	std::cout << "Sorting couples\n";
	// sort the pairs in result by the desire distance in ascending order:
	// the desire distance should be as small as posible
	std::sort(result.begin(), result.end(),
		[](const std::pair<std::pair<Person, Person>, float>& c1,
		   const std::pair<std::pair<Person, Person>, float>& c2)
		{
			return c1.second < c2.second;
		});

	std::cout << "Removing duplicated match results\n";
	// remove the couples whose desire distance is smaller and its candidate had been matched:
	for (size_t i = 0; i < result.size(); ++i)
	{
		const auto curPair = result[i];
		std::remove_if(std::next(result.begin() + i), result.end(),
			[curPair](const std::pair<std::pair<Person, Person>, float>& couple)
		{
				return curPair.first.first == couple.first.first ||
					curPair.first.first == couple.first.second ||
					curPair.first.second == couple.first.first ||
					curPair.first.second == couple.first.second;
		});
	}

	return result;
}
