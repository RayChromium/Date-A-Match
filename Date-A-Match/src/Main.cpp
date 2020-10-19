#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <csv2/reader.hpp>

int main()
{
	csv2::Reader<csv2::delimiter<','>,
		csv2::quote_character<'"'>,
		csv2::first_row_is_header<true>,
		csv2::trim_policy::trim_whitespace> csv_R;
	std::string temp;
	if (csv_R.mmap("test_01.csv"))
	{
		auto csvHead = csv_R.header();
		for (auto c : csvHead)
		{
			temp.erase(temp.begin(), temp.end());
			c.read_value(temp);
			std::cout << temp;
		}
		std::cout << std::endl;
		for (auto row : csv_R)
		{
			for (auto cell : row)
			{
				temp.erase(temp.begin(), temp.end());
				cell.read_value(temp);
				std::cout << temp;
			}
			std::cout << std::endl;
		}
	}
	std::cout << "Hello world!" << std::endl;
	std::cin.get();
	return 0;
}