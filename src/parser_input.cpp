#include "parser_input.hpp"
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>

// Data is in format: <size_t>:<size_t>
Input get_single_input(const std::string& data)
{
	Input result;
	size_t tmp;

	int vars_written = sscanf(data.data(), "%lu:%lu", &result.nodeID, &tmp);
	if(vars_written != 2)
	{
		return {};
	}

	result.value = tmp;
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

		while(ss >> single_input)
		{
			in.emplace_back(get_single_input(single_input));
		}

		result.emplace_back(in);
	}

	return result;
}