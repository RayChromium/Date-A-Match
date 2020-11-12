#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <csv2/reader.hpp>
#include <csv2/writer.hpp>
#include <set>
#include "Person.h"
#include "Match.h"

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
			std::cout << "Loading src data ...  \n";
			for (auto row : csv_R)
			{
				std::string temp;
				row.read_raw_value(temp);
				rowStrs.push_back(temp);
			}
		}

		// so...need to delete those who quit before sign up deadline
		// load a quit list:
		std::set<std::string> quitList;
		{
			csv2::Reader<csv2::delimiter<','>,
				csv2::quote_character<'"'>,
				csv2::first_row_is_header<true>,
				csv2::trim_policy::trim_whitespace> quitCsvReader;
			if (quitCsvReader.mmap("Quit-List.csv"))
			{
				std::cout << "Loading quit list data ... \n";
				for (auto row : quitCsvReader)
				{
					for (auto cell : row)
					{
						std::string temp;
						cell.read_value(temp);
						quitList.insert(temp);
					}
				}
			}
		}

		// delete the quiters from persons:
		std::cout << " Deleting quit members from the person vector ... ";
		std::remove_if(persons.begin(), persons.end(), [&quitList](const Person& p)
			{
				return quitList.find(p.name) != quitList.end();
			});

		std::cout << "Replacing commas with space ... \n";

		for (size_t i = 0; i < rowStrs.size(); ++i)
		{
			std::replace(rowStrs[i].begin(), rowStrs[i].end(), ',', ' ');
		}

		std::cout << "Extracting src data ... \n";

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

	std::vector<std::pair<std::pair<Person, Person>, float>> result = Male2FemaleDisireDistances(persons);

	// write the result to a csv output file:
	{
		std::ofstream matchResultOfstream("match_result.csv");
		csv2::Writer<csv2::delimiter<','>> csvWriter(matchResultOfstream);
		size_t total = result.size() * 2;
		std::vector<std::vector<std::string>> outputRows;
		std::vector<std::string> header{ "No.", "Name","QQ","Phone","Gender", "No.","Name","QQ","Phone","Gender", "Desire Distance" };
		csvWriter.write_row(header);
		for (size_t i = 0, num = 1; i < result.size() && num <= total; ++i)
		{
			std::vector<std::string> row;
			// every row contains info from male & female
			// with numbers attached
			row.push_back(std::to_string(num));
			num++;
			row.push_back(result[i].first.first.name);
			row.push_back(result[i].first.first.qq);
			row.push_back(result[i].first.first.phoneNumber);
			row.push_back(result[i].first.first.gender == Gender::Male ? "M" : "F");
			row.push_back(std::to_string(num));
			num++;
			row.push_back(result[i].first.second.name);
			row.push_back(result[i].first.second.qq);
			row.push_back(result[i].first.second.phoneNumber);
			row.push_back(result[i].first.second.gender == Gender::Male ? "M" : "F");
			row.push_back(std::to_string(result[i].second));
			outputRows.push_back(row);
		}
		std::cout << "Ready to write output ... \n";
		csvWriter.write_rows(outputRows);
		std::cout << "Output written\n";
	}
	std::cout << "Done!"<<std::endl;
	std::cin.get();
	return 0;
}