#pragma once
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

enum class Gender
{
	Male,
	Female,
	Count
};

class Person
{
public:
	Person(const std::string& name,
		   const std::string& qq,
		   const std::string& phoneNumber,
		   const std::vector<int>& srcAttr,
		   int genderVal)
		:
		name(name),
		qq(qq),
		phoneNumber(phoneNumber),
		attributes(srcAttr),
		gender(genderVal == 1 ? Gender::Male : Gender::Female)
	{
	}
	void Print()
	{
		std::cout << "姓名：" << name << " QQ: " << qq << " phone: " << phoneNumber << " Attrbutes: ";
		std::cout << " 性别： " << (gender == Gender::Male ? "男 " : "女 ");
		for (auto i : attributes)
		{
			std::cout << i << " ";
		}
		std::cout<<std::endl;
	}
private:
	std::string name;
	std::string qq;
	std::string phoneNumber;
	std::vector<int> attributes;
	Gender gender;
};