#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <csv2/reader.hpp>
#include "Person.h"

int main()
{
	csv2::Reader<csv2::delimiter<','>,
		csv2::quote_character<'"'>,
		csv2::first_row_is_header<true>,
		csv2::trim_policy::trim_whitespace> csv_R;
	std::vector<Person> persons;

	// load csv data into persons
	{
		std::vector<std::string> rowStrs;
		// load the rows as raw comma seperated strings into rowStrs
		if (csv_R.mmap("Date-Match-Test.csv"))
		{
			for (auto row : csv_R)
			{
				std::string temp;
				row.read_raw_value(temp);
				rowStrs.push_back(temp);
			}
		}

		for (size_t i = 0; i < rowStrs.size(); ++i)
		{
			std::replace(rowStrs[i].begin(), rowStrs[i].end(), ',', ' ');
		}

		// we don't really care about the header(attribute names)
		// the csv we're using should have attributes as follows:
		// 'name' 'qq' 'phonenumber' 'GenderVal' 'attribute'*53
		for (size_t i = 0; i < rowStrs.size(); ++i)
		{
			std::string name;
			std::string qq;
			std::string phoneNumber;
			std::string tempValStr;
			std::vector<int> attributes;
			std::stringstream ss(rowStrs[i]);
			std::string genderValStr;
			ss >> name;
			ss >> qq;
			ss >> phoneNumber;
			ss >> genderValStr;
			for (size_t i = 0; i < 53; ++i)
			{
				ss >> tempValStr;
				attributes.push_back(std::stoi(tempValStr));
			}
			persons.emplace_back(name, qq, phoneNumber, attributes, std::stoi(genderValStr));
		}
	}

	// test the loading results:
	for (auto p : persons)
	{
		p.Print();
	}

	std::cin.get();
	return 0;
}