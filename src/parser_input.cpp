#include "parser_input.hpp"
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>

// Data is in format: <size_t>:<size_t>
Input get_single_input(const std::string& data)
{
	Input result;
	std::stringstream ss(data);

	char tmp;

	if(!(ss >> result.nodeID && ss >> tmp && ss >> result.value))
	{
		return {};
	}

	return result;
}

std::vector<InputLine> get_inputs(const std::string& filename)
{
	std::vector<InputLine> result;
	std::string line;
	std::ifstream file(filename);
	if(!file)
	{
		return {};
	}

	while(std::getline(file, line))
	{
		InputLine in;
		std::string single_input;
		std::stringstream ss(line);

		while(ss >> single_input) // ss -> cała linia, single_input "1:0"
		{
			in.emplace_back(get_single_input(single_input));
		}

		result.emplace_back(in);
	}

	return result;
}