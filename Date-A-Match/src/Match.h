#pragma once
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include "Person.h"

// this file contains matching functions declarations

std::vector<std::pair<std::pair<Person,Person>,float>>
Male2FemaleDisireDistances(std::vector<Person> persons);