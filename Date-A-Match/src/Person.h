#pragma once
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

enum class Gender
{
	Male,
	Female,
	Count
};

struct Person
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
	void Print() const
	{
		std::cout << "姓名：" << name << " QQ: " << qq << " phone: " << phoneNumber << " Attrbutes: ";
		std::cout << " 性别： " << (gender == Gender::Male ? "男 " : "女 ");
		for (auto i : attributes)
		{
			std::cout << i << " ";
		}
		std::cout<<std::endl;
	}
	float DesireDistance(const Person& another) const
	{
		float result = 0.0f;
		for (size_t i = 0; i < 53; ++i)
		{
			result += pow(attributes[i] - another.attributes[i], 2);
		}
		result = sqrt(result);
		return result;
	}
	bool IsMale()const
	{
		return gender == Gender::Male;
	}
	bool operator==(const Person& rhs)const
	{
		return name == rhs.name &&
			qq == rhs.qq &&
			phoneNumber == rhs.phoneNumber &&
			gender == rhs.gender;
	}
	std::string name;
	std::string qq;
	std::string phoneNumber;
	std::vector<int> attributes;
	Gender gender;
};